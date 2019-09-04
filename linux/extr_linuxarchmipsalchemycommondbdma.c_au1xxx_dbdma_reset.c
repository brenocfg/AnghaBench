#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {TYPE_2__* chan_desc_base; TYPE_2__* cur_ptr; TYPE_2__* put_ptr; TYPE_2__* get_ptr; } ;
typedef  TYPE_1__ chan_tab_t ;
struct TYPE_5__ {int /*<<< orphan*/  dscr_nxtptr; scalar_t__ sw_status; int /*<<< orphan*/  dscr_cmd0; } ;
typedef  TYPE_2__ au1x_ddma_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_CMD0_V ; 
 int /*<<< orphan*/  DSCR_GET_NXTPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xxx_dbdma_stop (scalar_t__) ; 
 TYPE_2__* phys_to_virt (int /*<<< orphan*/ ) ; 

void au1xxx_dbdma_reset(u32 chanid)
{
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	au1xxx_dbdma_stop(chanid);

	ctp = *((chan_tab_t **)chanid);
	ctp->get_ptr = ctp->put_ptr = ctp->cur_ptr = ctp->chan_desc_base;

	/* Run through the descriptors and reset the valid indicator. */
	dp = ctp->chan_desc_base;

	do {
		dp->dscr_cmd0 &= ~DSCR_CMD0_V;
		/*
		 * Reset our software status -- this is used to determine
		 * if a descriptor is in use by upper level software. Since
		 * posting can reset 'V' bit.
		 */
		dp->sw_status = 0;
		dp = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));
	} while (dp != ctp->chan_desc_base);
}