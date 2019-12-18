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
struct tm6000_core {struct tm6000_IR* ir; } ;
struct tm6000_IR {int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int __tm6000_ir_int_start (int /*<<< orphan*/ ) ; 

int tm6000_ir_int_start(struct tm6000_core *dev)
{
	struct tm6000_IR *ir = dev->ir;

	if (!ir)
		return 0;

	return __tm6000_ir_int_start(ir->rc);
}