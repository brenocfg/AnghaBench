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
struct addr_val_pair {int /*<<< orphan*/  val; scalar_t__ reg_addr; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  t3_write_reg (struct adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

void t3_write_regs(struct adapter *adapter, const struct addr_val_pair *p,
		   int n, unsigned int offset)
{
	while (n--) {
		t3_write_reg(adapter, p->reg_addr + offset, p->val);
		p++;
	}
}