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

/* Variables and functions */

__attribute__((used)) static void check_parms(void)
{
#ifdef HAVE_DIE_NMI
	int do_nmi = 0;
	int rv;

	if (preaction_val == WDOG_PRETIMEOUT_NMI) {
		do_nmi = 1;
		if (preop_val == WDOG_PREOP_GIVE_DATA) {
			pr_warn(PFX "Pretimeout op is to give data but NMI pretimeout is enabled, setting pretimeout op to none\n");
			preop_op("preop_none", NULL);
			do_nmi = 0;
		}
	}
	if (do_nmi && !nmi_handler_registered) {
		rv = register_nmi_handler(NMI_UNKNOWN, ipmi_nmi, 0,
						"ipmi");
		if (rv) {
			pr_warn(PFX "Can't register nmi handler\n");
			return;
		} else
			nmi_handler_registered = 1;
	} else if (!do_nmi && nmi_handler_registered) {
		unregister_nmi_handler(NMI_UNKNOWN, "ipmi");
		nmi_handler_registered = 0;
	}
#endif
}