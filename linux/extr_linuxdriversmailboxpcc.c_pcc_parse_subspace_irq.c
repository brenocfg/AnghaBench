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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int bit_width; int /*<<< orphan*/  address; } ;
struct acpi_pcct_hw_reduced_type2 {TYPE_2__ platform_ack_register; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct acpi_pcct_hw_reduced {TYPE_1__ header; int /*<<< orphan*/  platform_interrupt; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE_TYPE2 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  acpi_os_ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pcc_doorbell_ack_vaddr ; 
 scalar_t__* pcc_doorbell_irq ; 
 scalar_t__ pcc_map_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int pcc_parse_subspace_irq(int id,
				  struct acpi_pcct_hw_reduced *pcct_ss)
{
	pcc_doorbell_irq[id] = pcc_map_interrupt(pcct_ss->platform_interrupt,
						 (u32)pcct_ss->flags);
	if (pcc_doorbell_irq[id] <= 0) {
		pr_err("PCC GSI %d not registered\n",
		       pcct_ss->platform_interrupt);
		return -EINVAL;
	}

	if (pcct_ss->header.type
		== ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE_TYPE2) {
		struct acpi_pcct_hw_reduced_type2 *pcct2_ss = (void *)pcct_ss;

		pcc_doorbell_ack_vaddr[id] = acpi_os_ioremap(
				pcct2_ss->platform_ack_register.address,
				pcct2_ss->platform_ack_register.bit_width / 8);
		if (!pcc_doorbell_ack_vaddr[id]) {
			pr_err("Failed to ioremap PCC ACK register\n");
			return -ENOMEM;
		}
	}

	return 0;
}