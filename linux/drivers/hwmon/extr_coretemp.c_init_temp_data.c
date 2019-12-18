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
struct temp_data {int is_pkg_data; unsigned int cpu; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  attr_size; int /*<<< orphan*/  cpu_core_id; int /*<<< orphan*/  status_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_CORE_ATTRS ; 
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_STATUS ; 
 int /*<<< orphan*/  MSR_IA32_THERM_STATUS ; 
 int /*<<< orphan*/  TO_CORE_ID (unsigned int) ; 
 struct temp_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct temp_data *init_temp_data(unsigned int cpu, int pkg_flag)
{
	struct temp_data *tdata;

	tdata = kzalloc(sizeof(struct temp_data), GFP_KERNEL);
	if (!tdata)
		return NULL;

	tdata->status_reg = pkg_flag ? MSR_IA32_PACKAGE_THERM_STATUS :
							MSR_IA32_THERM_STATUS;
	tdata->is_pkg_data = pkg_flag;
	tdata->cpu = cpu;
	tdata->cpu_core_id = TO_CORE_ID(cpu);
	tdata->attr_size = MAX_CORE_ATTRS;
	mutex_init(&tdata->update_lock);
	return tdata;
}