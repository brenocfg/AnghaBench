#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct bfa_ioc_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 scalar_t__ BFI_IOC_DISABLED ; 
 scalar_t__ BFI_IOC_FAIL ; 
 scalar_t__ BFI_IOC_INITING ; 
 scalar_t__ BFI_IOC_MEMTEST ; 
 scalar_t__ BFI_IOC_OP ; 
 scalar_t__ BFI_IOC_UNINIT ; 
 scalar_t__ bfa_ioc_cb_get_alt_ioc_fwstate (struct bfa_ioc_s*) ; 
 scalar_t__ bfa_ioc_cb_get_cur_ioc_fwstate (struct bfa_ioc_s*) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioc_cb_sync_complete(struct bfa_ioc_s *ioc)
{
	u32 fwstate, alt_fwstate;
	fwstate = bfa_ioc_cb_get_cur_ioc_fwstate(ioc);

	/*
	 * At this point, this IOC is hoding the hw sem in the
	 * start path (fwcheck) OR in the disable/enable path
	 * OR to check if the other IOC has acknowledged failure.
	 *
	 * So, this IOC can be in UNINIT, INITING, DISABLED, FAIL
	 * or in MEMTEST states. In a normal scenario, this IOC
	 * can not be in OP state when this function is called.
	 *
	 * However, this IOC could still be in OP state when
	 * the OS driver is starting up, if the OptROM code has
	 * left it in that state.
	 *
	 * If we had marked this IOC's fwstate as BFI_IOC_FAIL
	 * in the failure case and now, if the fwstate is not
	 * BFI_IOC_FAIL it implies that the other PCI fn have
	 * reinitialized the ASIC or this IOC got disabled, so
	 * return TRUE.
	 */
	if (fwstate == BFI_IOC_UNINIT ||
		fwstate == BFI_IOC_INITING ||
		fwstate == BFI_IOC_DISABLED ||
		fwstate == BFI_IOC_MEMTEST ||
		fwstate == BFI_IOC_OP)
		return BFA_TRUE;
	else {
		alt_fwstate = bfa_ioc_cb_get_alt_ioc_fwstate(ioc);
		if (alt_fwstate == BFI_IOC_FAIL ||
			alt_fwstate == BFI_IOC_DISABLED ||
			alt_fwstate == BFI_IOC_UNINIT ||
			alt_fwstate == BFI_IOC_INITING ||
			alt_fwstate == BFI_IOC_MEMTEST)
			return BFA_TRUE;
		else
			return BFA_FALSE;
	}
}