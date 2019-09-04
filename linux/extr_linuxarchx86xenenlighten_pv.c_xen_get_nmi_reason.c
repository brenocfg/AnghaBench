#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nmi_reason; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 TYPE_2__* HYPERVISOR_shared_info ; 
 unsigned char NMI_REASON_IOCHK ; 
 unsigned char NMI_REASON_SERR ; 
 int /*<<< orphan*/  _XEN_NMIREASON_io_error ; 
 int /*<<< orphan*/  _XEN_NMIREASON_pci_serr ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned char xen_get_nmi_reason(void)
{
	unsigned char reason = 0;

	/* Construct a value which looks like it came from port 0x61. */
	if (test_bit(_XEN_NMIREASON_io_error,
		     &HYPERVISOR_shared_info->arch.nmi_reason))
		reason |= NMI_REASON_IOCHK;
	if (test_bit(_XEN_NMIREASON_pci_serr,
		     &HYPERVISOR_shared_info->arch.nmi_reason))
		reason |= NMI_REASON_SERR;

	return reason;
}