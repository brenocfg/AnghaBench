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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct smi_info {int cannot_disable_irq; int irq_enable_broken; TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_BMC_RCV_MSG_INTR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int get_global_enables (struct smi_info*,int /*<<< orphan*/ *) ; 
 int set_global_enables (struct smi_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_set_rcv_irq(struct smi_info *smi_info)
{
	u8 enables = 0;
	int rv;

	if (!smi_info->io.irq)
		return;

	rv = get_global_enables(smi_info, &enables);
	if (!rv) {
		enables |= IPMI_BMC_RCV_MSG_INTR;
		rv = set_global_enables(smi_info, enables);
	}

	if (rv < 0) {
		dev_err(smi_info->io.dev,
			"Cannot check setting the rcv irq: %d\n", rv);
		return;
	}

	if (rv) {
		/*
		 * An error when setting the event buffer bit means
		 * setting the bit is not supported.
		 */
		dev_warn(smi_info->io.dev,
			 "The BMC does not support setting the recv irq bit, compensating, but the BMC needs to be fixed.\n");
		smi_info->cannot_disable_irq = true;
		smi_info->irq_enable_broken = true;
	}
}