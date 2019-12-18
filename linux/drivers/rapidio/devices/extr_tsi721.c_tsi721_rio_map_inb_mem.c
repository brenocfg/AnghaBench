#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct tsi721_ib_win_mapping {int lstart; int /*<<< orphan*/  node; } ;
struct tsi721_ib_win {int active; int rstart; int size; int xlat; int lstart; int /*<<< orphan*/  mappings; } ;
struct tsi721_device {scalar_t__ ibwin_cnt; TYPE_1__* pdev; scalar_t__ regs; struct tsi721_ib_win* ib_win; } ;
struct rio_mport {struct tsi721_device* priv; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IBW ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ TSI721_IBWIN_LB (int) ; 
 int TSI721_IBWIN_LB_BA ; 
 int TSI721_IBWIN_LB_WEN ; 
 int TSI721_IBWIN_NUM ; 
 int TSI721_IBWIN_SIZE (int) ; 
 scalar_t__ TSI721_IBWIN_SZ (int) ; 
 scalar_t__ TSI721_IBWIN_TLA (int) ; 
 int TSI721_IBWIN_TLA_ADD ; 
 scalar_t__ TSI721_IBWIN_TUA (int) ; 
 scalar_t__ TSI721_IBWIN_UB (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  kfree (struct tsi721_ib_win_mapping*) ; 
 struct tsi721_ib_win_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,...) ; 

__attribute__((used)) static int tsi721_rio_map_inb_mem(struct rio_mport *mport, dma_addr_t lstart,
		u64 rstart, u64 size, u32 flags)
{
	struct tsi721_device *priv = mport->priv;
	int i, avail = -1;
	u32 regval;
	struct tsi721_ib_win *ib_win;
	bool direct = (lstart == rstart);
	u64 ibw_size;
	dma_addr_t loc_start;
	u64 ibw_start;
	struct tsi721_ib_win_mapping *map = NULL;
	int ret = -EBUSY;

	/* Max IBW size supported by HW is 16GB */
	if (size > 0x400000000UL)
		return -EINVAL;

	if (direct) {
		/* Calculate minimal acceptable window size and base address */

		ibw_size = roundup_pow_of_two(size);
		ibw_start = lstart & ~(ibw_size - 1);

		tsi_debug(IBW, &priv->pdev->dev,
			"Direct (RIO_0x%llx -> PCIe_%pad), size=0x%llx, ibw_start = 0x%llx",
			rstart, &lstart, size, ibw_start);

		while ((lstart + size) > (ibw_start + ibw_size)) {
			ibw_size *= 2;
			ibw_start = lstart & ~(ibw_size - 1);
			/* Check for crossing IBW max size 16GB */
			if (ibw_size > 0x400000000UL)
				return -EBUSY;
		}

		loc_start = ibw_start;

		map = kzalloc(sizeof(struct tsi721_ib_win_mapping), GFP_ATOMIC);
		if (map == NULL)
			return -ENOMEM;

	} else {
		tsi_debug(IBW, &priv->pdev->dev,
			"Translated (RIO_0x%llx -> PCIe_%pad), size=0x%llx",
			rstart, &lstart, size);

		if (!is_power_of_2(size) || size < 0x1000 ||
		    ((u64)lstart & (size - 1)) || (rstart & (size - 1)))
			return -EINVAL;
		if (priv->ibwin_cnt == 0)
			return -EBUSY;
		ibw_start = rstart;
		ibw_size = size;
		loc_start = lstart;
	}

	/*
	 * Scan for overlapping with active regions and mark the first available
	 * IB window at the same time.
	 */
	for (i = 0; i < TSI721_IBWIN_NUM; i++) {
		ib_win = &priv->ib_win[i];

		if (!ib_win->active) {
			if (avail == -1) {
				avail = i;
				ret = 0;
			}
		} else if (ibw_start < (ib_win->rstart + ib_win->size) &&
			   (ibw_start + ibw_size) > ib_win->rstart) {
			/* Return error if address translation involved */
			if (!direct || ib_win->xlat) {
				ret = -EFAULT;
				break;
			}

			/*
			 * Direct mappings usually are larger than originally
			 * requested fragments - check if this new request fits
			 * into it.
			 */
			if (rstart >= ib_win->rstart &&
			    (rstart + size) <= (ib_win->rstart +
							ib_win->size)) {
				/* We are in - no further mapping required */
				map->lstart = lstart;
				list_add_tail(&map->node, &ib_win->mappings);
				return 0;
			}

			ret = -EFAULT;
			break;
		}
	}

	if (ret)
		goto out;
	i = avail;

	/* Sanity check: available IB window must be disabled at this point */
	regval = ioread32(priv->regs + TSI721_IBWIN_LB(i));
	if (WARN_ON(regval & TSI721_IBWIN_LB_WEN)) {
		ret = -EIO;
		goto out;
	}

	ib_win = &priv->ib_win[i];
	ib_win->active = true;
	ib_win->rstart = ibw_start;
	ib_win->lstart = loc_start;
	ib_win->size = ibw_size;
	ib_win->xlat = (lstart != rstart);
	INIT_LIST_HEAD(&ib_win->mappings);

	/*
	 * When using direct IBW mapping and have larger than requested IBW size
	 * we can have multiple local memory blocks mapped through the same IBW
	 * To handle this situation we maintain list of "clients" for such IBWs.
	 */
	if (direct) {
		map->lstart = lstart;
		list_add_tail(&map->node, &ib_win->mappings);
	}

	iowrite32(TSI721_IBWIN_SIZE(ibw_size) << 8,
			priv->regs + TSI721_IBWIN_SZ(i));

	iowrite32(((u64)loc_start >> 32), priv->regs + TSI721_IBWIN_TUA(i));
	iowrite32(((u64)loc_start & TSI721_IBWIN_TLA_ADD),
		  priv->regs + TSI721_IBWIN_TLA(i));

	iowrite32(ibw_start >> 32, priv->regs + TSI721_IBWIN_UB(i));
	iowrite32((ibw_start & TSI721_IBWIN_LB_BA) | TSI721_IBWIN_LB_WEN,
		priv->regs + TSI721_IBWIN_LB(i));

	priv->ibwin_cnt--;

	tsi_debug(IBW, &priv->pdev->dev,
		"Configured IBWIN%d (RIO_0x%llx -> PCIe_%pad), size=0x%llx",
		i, ibw_start, &loc_start, ibw_size);

	return 0;
out:
	kfree(map);
	return ret;
}