#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct idt_ntb_dev {TYPE_2__ ntb; } ;
struct idt_ntb_bar {int /*<<< orphan*/  setup; } ;
struct idt_mw_cfg {int type; unsigned char bar; unsigned char idx; int size_max; int size_align; int /*<<< orphan*/  addr_align; } ;
typedef  enum idt_mw_type { ____Placeholder_idt_mw_type } idt_mw_type ;
struct TYPE_6__ {struct idt_ntb_bar* bars; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARSETUP_ATRAN ; 
 int /*<<< orphan*/  BARSETUP_SIZE ; 
 int /*<<< orphan*/  BARSETUP_TYPE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct idt_mw_cfg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GET_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IDT_BARSETUP_EN ; 
 int IDT_BARSETUP_MODE_CFG ; 
 unsigned char IDT_BAR_CNT ; 
 int IDT_DIR_SIZE_ALIGN ; 
 int IDT_MAX_NR_MWS ; 
 int IDT_MW_DIR ; 
 int IDT_MW_LUT12 ; 
 int /*<<< orphan*/  IDT_TRANS_ALIGN ; 
 int IS_FLD_SET (int /*<<< orphan*/ ,int,int) ; 
 struct idt_mw_cfg* devm_kcalloc (int /*<<< orphan*/ *,unsigned char,int,int /*<<< orphan*/ ) ; 
 unsigned char idt_get_mw_count (int) ; 
 int idt_sw_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct idt_mw_cfg*,struct idt_mw_cfg*,unsigned char) ; 
 TYPE_3__* portdata_tbl ; 

__attribute__((used)) static struct idt_mw_cfg *idt_scan_mws(struct idt_ntb_dev *ndev, int port,
				       unsigned char *mw_cnt)
{
	struct idt_mw_cfg mws[IDT_MAX_NR_MWS], *ret_mws;
	const struct idt_ntb_bar *bars;
	enum idt_mw_type mw_type;
	unsigned char widx, bidx, en_cnt;
	bool bar_64bit = false;
	int aprt_size;
	u32 data;

	/* Retrieve the array of the BARs registers */
	bars = portdata_tbl[port].bars;

	/* Scan all the BARs belonging to the port */
	*mw_cnt = 0;
	for (bidx = 0; bidx < IDT_BAR_CNT; bidx += 1 + bar_64bit) {
		/* Read BARSETUP register value */
		data = idt_sw_read(ndev, bars[bidx].setup);

		/* Skip disabled BARs */
		if (!(data & IDT_BARSETUP_EN)) {
			bar_64bit = false;
			continue;
		}

		/* Skip next BARSETUP if current one has 64bit addressing */
		bar_64bit = IS_FLD_SET(BARSETUP_TYPE, data, 64);

		/* Skip configuration space mapping BARs */
		if (data & IDT_BARSETUP_MODE_CFG)
			continue;

		/* Retrieve MW type/entries count and aperture size */
		mw_type = GET_FIELD(BARSETUP_ATRAN, data);
		en_cnt = idt_get_mw_count(mw_type);
		aprt_size = (u64)1 << GET_FIELD(BARSETUP_SIZE, data);

		/* Save configurations of all available memory windows */
		for (widx = 0; widx < en_cnt; widx++, (*mw_cnt)++) {
			/*
			 * IDT can expose a limited number of MWs, so it's bug
			 * to have more than the driver expects
			 */
			if (*mw_cnt >= IDT_MAX_NR_MWS)
				return ERR_PTR(-EINVAL);

			/* Save basic MW info */
			mws[*mw_cnt].type = mw_type;
			mws[*mw_cnt].bar = bidx;
			mws[*mw_cnt].idx = widx;
			/* It's always DWORD aligned */
			mws[*mw_cnt].addr_align = IDT_TRANS_ALIGN;
			/* DIR and LUT approachs differently configure MWs */
			if (mw_type == IDT_MW_DIR)
				mws[*mw_cnt].size_max = aprt_size;
			else if (mw_type == IDT_MW_LUT12)
				mws[*mw_cnt].size_max = aprt_size / 16;
			else
				mws[*mw_cnt].size_max = aprt_size / 32;
			mws[*mw_cnt].size_align = (mw_type == IDT_MW_DIR) ?
				IDT_DIR_SIZE_ALIGN : mws[*mw_cnt].size_max;
		}
	}

	/* Allocate memory for memory window descriptors */
	ret_mws = devm_kcalloc(&ndev->ntb.pdev->dev, *mw_cnt, sizeof(*ret_mws),
			       GFP_KERNEL);
	if (!ret_mws)
		return ERR_PTR(-ENOMEM);

	/* Copy the info of detected memory windows */
	memcpy(ret_mws, mws, (*mw_cnt)*sizeof(*ret_mws));

	return ret_mws;
}