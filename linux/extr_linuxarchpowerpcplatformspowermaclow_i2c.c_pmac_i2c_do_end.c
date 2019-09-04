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
struct pmf_function {int dummy; } ;
struct pmac_i2c_pf_inst {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pmac_i2c_pf_inst*) ; 
 int /*<<< orphan*/  pmac_i2c_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmac_i2c_do_end(struct pmf_function *func, void *instdata)
{
	struct pmac_i2c_pf_inst *inst = instdata;

	if (inst == NULL)
		return;
	pmac_i2c_close(inst->bus);
	kfree(inst);
}