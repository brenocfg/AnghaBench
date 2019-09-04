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
struct TYPE_2__ {scalar_t__ irq; } ;
struct smi_info {int interrupt_disabled; TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  start_check_enables (struct smi_info*) ; 

__attribute__((used)) static inline bool disable_si_irq(struct smi_info *smi_info)
{
	if ((smi_info->io.irq) && (!smi_info->interrupt_disabled)) {
		smi_info->interrupt_disabled = true;
		start_check_enables(smi_info);
		return true;
	}
	return false;
}