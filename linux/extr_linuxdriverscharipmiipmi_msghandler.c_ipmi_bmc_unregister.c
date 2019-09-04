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
struct ipmi_smi {int /*<<< orphan*/  bmc_reg_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipmi_bmc_unregister (struct ipmi_smi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmi_bmc_unregister(struct ipmi_smi *intf)
{
	mutex_lock(&intf->bmc_reg_mutex);
	__ipmi_bmc_unregister(intf);
	mutex_unlock(&intf->bmc_reg_mutex);
}