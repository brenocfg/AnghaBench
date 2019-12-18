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
struct pci_fixup {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  enum pci_fixup_pass { ____Placeholder_pci_fixup_pass } pci_fixup_pass ;

/* Variables and functions */
 struct pci_fixup* __end_pci_fixups_early ; 
 struct pci_fixup* __end_pci_fixups_enable ; 
 struct pci_fixup* __end_pci_fixups_final ; 
 struct pci_fixup* __end_pci_fixups_header ; 
 struct pci_fixup* __end_pci_fixups_resume ; 
 struct pci_fixup* __end_pci_fixups_resume_early ; 
 struct pci_fixup* __end_pci_fixups_suspend ; 
 struct pci_fixup* __end_pci_fixups_suspend_late ; 
 struct pci_fixup* __start_pci_fixups_early ; 
 struct pci_fixup* __start_pci_fixups_enable ; 
 struct pci_fixup* __start_pci_fixups_final ; 
 struct pci_fixup* __start_pci_fixups_header ; 
 struct pci_fixup* __start_pci_fixups_resume ; 
 struct pci_fixup* __start_pci_fixups_resume_early ; 
 struct pci_fixup* __start_pci_fixups_suspend ; 
 struct pci_fixup* __start_pci_fixups_suspend_late ; 
 int /*<<< orphan*/  pci_apply_fixup_final_quirks ; 
 int /*<<< orphan*/  pci_do_fixups (struct pci_dev*,struct pci_fixup*,struct pci_fixup*) ; 
#define  pci_fixup_early 135 
#define  pci_fixup_enable 134 
#define  pci_fixup_final 133 
#define  pci_fixup_header 132 
#define  pci_fixup_resume 131 
#define  pci_fixup_resume_early 130 
#define  pci_fixup_suspend 129 
#define  pci_fixup_suspend_late 128 

void pci_fixup_device(enum pci_fixup_pass pass, struct pci_dev *dev)
{
	struct pci_fixup *start, *end;

	switch (pass) {
	case pci_fixup_early:
		start = __start_pci_fixups_early;
		end = __end_pci_fixups_early;
		break;

	case pci_fixup_header:
		start = __start_pci_fixups_header;
		end = __end_pci_fixups_header;
		break;

	case pci_fixup_final:
		if (!pci_apply_fixup_final_quirks)
			return;
		start = __start_pci_fixups_final;
		end = __end_pci_fixups_final;
		break;

	case pci_fixup_enable:
		start = __start_pci_fixups_enable;
		end = __end_pci_fixups_enable;
		break;

	case pci_fixup_resume:
		start = __start_pci_fixups_resume;
		end = __end_pci_fixups_resume;
		break;

	case pci_fixup_resume_early:
		start = __start_pci_fixups_resume_early;
		end = __end_pci_fixups_resume_early;
		break;

	case pci_fixup_suspend:
		start = __start_pci_fixups_suspend;
		end = __end_pci_fixups_suspend;
		break;

	case pci_fixup_suspend_late:
		start = __start_pci_fixups_suspend_late;
		end = __end_pci_fixups_suspend_late;
		break;

	default:
		/* stupid compiler warning, you would think with an enum... */
		return;
	}
	pci_do_fixups(dev, start, end);
}