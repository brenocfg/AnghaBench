#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int dev_id; int dev_devwidth; int dev_flags; int dev_tsize; int dev_physaddr; } ;
typedef  TYPE_1__ dbdev_tab_t ;
struct TYPE_6__ {int cdb_membase; TYPE_3__* chan_desc_base; TYPE_3__* cur_ptr; TYPE_3__* put_ptr; TYPE_3__* get_ptr; TYPE_1__* chan_dest; TYPE_1__* chan_src; } ;
typedef  TYPE_2__ chan_tab_t ;
struct TYPE_7__ {int dscr_cmd0; int dscr_cmd1; int dscr_source0; int dscr_source1; int dscr_dest0; int dscr_dest1; void* dscr_nxtptr; scalar_t__ sw_status; scalar_t__ sw_context; scalar_t__ dscr_stat; } ;
typedef  TYPE_3__ au1x_ddma_desc_t ;

/* Variables and functions */
 int ALIGN_ADDR (int,int) ; 
 int DEV_FLAGS_BURSTABLE ; 
 int DEV_FLAGS_IN ; 
 int DEV_FLAGS_OUT ; 
 scalar_t__ DSCR_CMD0_ALWAYS ; 
 int /*<<< orphan*/  DSCR_CMD0_BYTE ; 
 int DSCR_CMD0_CV ; 
 int DSCR_CMD0_DID (int) ; 
 int DSCR_CMD0_DN ; 
 int DSCR_CMD0_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSCR_CMD0_HALFWORD ; 
 int DSCR_CMD0_IE ; 
 int DSCR_CMD0_MEM ; 
 int DSCR_CMD0_SID (int) ; 
 int DSCR_CMD0_SN ; 
 int DSCR_CMD0_ST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSCR_CMD0_ST_NOCHANGE ; 
 int DSCR_CMD0_SW (int /*<<< orphan*/ ) ; 
 scalar_t__ DSCR_CMD0_THROTTLE ; 
 int /*<<< orphan*/  DSCR_CMD0_WORD ; 
 scalar_t__ DSCR_CUSTOM2DEV_ID (int) ; 
 int DSCR_DEST1_DAM (int /*<<< orphan*/ ) ; 
 int DSCR_DEST1_DTS (int /*<<< orphan*/ ) ; 
 void* DSCR_NXTPTR (int /*<<< orphan*/ ) ; 
 int DSCR_SRC1_SAM (int /*<<< orphan*/ ) ; 
 int DSCR_SRC1_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSCR_xAM_BURST ; 
 int /*<<< orphan*/  DSCR_xAM_STATIC ; 
 int /*<<< orphan*/  DSCR_xTS_SIZE1 ; 
 int /*<<< orphan*/  DSCR_xTS_SIZE2 ; 
 int /*<<< orphan*/  DSCR_xTS_SIZE4 ; 
 int /*<<< orphan*/  DSCR_xTS_SIZE8 ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void const*) ; 
 scalar_t__ kmalloc (int,int) ; 
 scalar_t__ kmalloc_array (int,int,int) ; 
 int /*<<< orphan*/  virt_to_phys (TYPE_3__*) ; 

u32 au1xxx_dbdma_ring_alloc(u32 chanid, int entries)
{
	int			i;
	u32			desc_base, srcid, destid;
	u32			cmd0, cmd1, src1, dest1;
	u32			src0, dest0;
	chan_tab_t		*ctp;
	dbdev_tab_t		*stp, *dtp;
	au1x_ddma_desc_t	*dp;

	/*
	 * I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_src;
	dtp = ctp->chan_dest;

	/*
	 * The descriptors must be 32-byte aligned.  There is a
	 * possibility the allocation will give us such an address,
	 * and if we try that first we are likely to not waste larger
	 * slabs of memory.
	 */
	desc_base = (u32)kmalloc_array(entries, sizeof(au1x_ddma_desc_t),
				       GFP_KERNEL|GFP_DMA);
	if (desc_base == 0)
		return 0;

	if (desc_base & 0x1f) {
		/*
		 * Lost....do it again, allocate extra, and round
		 * the address base.
		 */
		kfree((const void *)desc_base);
		i = entries * sizeof(au1x_ddma_desc_t);
		i += (sizeof(au1x_ddma_desc_t) - 1);
		desc_base = (u32)kmalloc(i, GFP_KERNEL|GFP_DMA);
		if (desc_base == 0)
			return 0;

		ctp->cdb_membase = desc_base;
		desc_base = ALIGN_ADDR(desc_base, sizeof(au1x_ddma_desc_t));
	} else
		ctp->cdb_membase = desc_base;

	dp = (au1x_ddma_desc_t *)desc_base;

	/* Keep track of the base descriptor. */
	ctp->chan_desc_base = dp;

	/* Initialize the rings with as much information as we know. */
	srcid = stp->dev_id;
	destid = dtp->dev_id;

	cmd0 = cmd1 = src1 = dest1 = 0;
	src0 = dest0 = 0;

	cmd0 |= DSCR_CMD0_SID(srcid);
	cmd0 |= DSCR_CMD0_DID(destid);
	cmd0 |= DSCR_CMD0_IE | DSCR_CMD0_CV;
	cmd0 |= DSCR_CMD0_ST(DSCR_CMD0_ST_NOCHANGE);

	/* Is it mem to mem transfer? */
	if (((DSCR_CUSTOM2DEV_ID(srcid) == DSCR_CMD0_THROTTLE) ||
	     (DSCR_CUSTOM2DEV_ID(srcid) == DSCR_CMD0_ALWAYS)) &&
	    ((DSCR_CUSTOM2DEV_ID(destid) == DSCR_CMD0_THROTTLE) ||
	     (DSCR_CUSTOM2DEV_ID(destid) == DSCR_CMD0_ALWAYS)))
		cmd0 |= DSCR_CMD0_MEM;

	switch (stp->dev_devwidth) {
	case 8:
		cmd0 |= DSCR_CMD0_SW(DSCR_CMD0_BYTE);
		break;
	case 16:
		cmd0 |= DSCR_CMD0_SW(DSCR_CMD0_HALFWORD);
		break;
	case 32:
	default:
		cmd0 |= DSCR_CMD0_SW(DSCR_CMD0_WORD);
		break;
	}

	switch (dtp->dev_devwidth) {
	case 8:
		cmd0 |= DSCR_CMD0_DW(DSCR_CMD0_BYTE);
		break;
	case 16:
		cmd0 |= DSCR_CMD0_DW(DSCR_CMD0_HALFWORD);
		break;
	case 32:
	default:
		cmd0 |= DSCR_CMD0_DW(DSCR_CMD0_WORD);
		break;
	}

	/*
	 * If the device is marked as an in/out FIFO, ensure it is
	 * set non-coherent.
	 */
	if (stp->dev_flags & DEV_FLAGS_IN)
		cmd0 |= DSCR_CMD0_SN;		/* Source in FIFO */
	if (dtp->dev_flags & DEV_FLAGS_OUT)
		cmd0 |= DSCR_CMD0_DN;		/* Destination out FIFO */

	/*
	 * Set up source1.  For now, assume no stride and increment.
	 * A channel attribute update can change this later.
	 */
	switch (stp->dev_tsize) {
	case 1:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE1);
		break;
	case 2:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE2);
		break;
	case 4:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE4);
		break;
	case 8:
	default:
		src1 |= DSCR_SRC1_STS(DSCR_xTS_SIZE8);
		break;
	}

	/* If source input is FIFO, set static address. */
	if (stp->dev_flags & DEV_FLAGS_IN) {
		if (stp->dev_flags & DEV_FLAGS_BURSTABLE)
			src1 |= DSCR_SRC1_SAM(DSCR_xAM_BURST);
		else
			src1 |= DSCR_SRC1_SAM(DSCR_xAM_STATIC);
	}

	if (stp->dev_physaddr)
		src0 = stp->dev_physaddr;

	/*
	 * Set up dest1.  For now, assume no stride and increment.
	 * A channel attribute update can change this later.
	 */
	switch (dtp->dev_tsize) {
	case 1:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE1);
		break;
	case 2:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE2);
		break;
	case 4:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE4);
		break;
	case 8:
	default:
		dest1 |= DSCR_DEST1_DTS(DSCR_xTS_SIZE8);
		break;
	}

	/* If destination output is FIFO, set static address. */
	if (dtp->dev_flags & DEV_FLAGS_OUT) {
		if (dtp->dev_flags & DEV_FLAGS_BURSTABLE)
			dest1 |= DSCR_DEST1_DAM(DSCR_xAM_BURST);
		else
			dest1 |= DSCR_DEST1_DAM(DSCR_xAM_STATIC);
	}

	if (dtp->dev_physaddr)
		dest0 = dtp->dev_physaddr;

#if 0
		printk(KERN_DEBUG "did:%x sid:%x cmd0:%x cmd1:%x source0:%x "
				  "source1:%x dest0:%x dest1:%x\n",
				  dtp->dev_id, stp->dev_id, cmd0, cmd1, src0,
				  src1, dest0, dest1);
#endif
	for (i = 0; i < entries; i++) {
		dp->dscr_cmd0 = cmd0;
		dp->dscr_cmd1 = cmd1;
		dp->dscr_source0 = src0;
		dp->dscr_source1 = src1;
		dp->dscr_dest0 = dest0;
		dp->dscr_dest1 = dest1;
		dp->dscr_stat = 0;
		dp->sw_context = 0;
		dp->sw_status = 0;
		dp->dscr_nxtptr = DSCR_NXTPTR(virt_to_phys(dp + 1));
		dp++;
	}

	/* Make last descrptor point to the first. */
	dp--;
	dp->dscr_nxtptr = DSCR_NXTPTR(virt_to_phys(ctp->chan_desc_base));
	ctp->get_ptr = ctp->put_ptr = ctp->cur_ptr = ctp->chan_desc_base;

	return (u32)ctp->chan_desc_base;
}