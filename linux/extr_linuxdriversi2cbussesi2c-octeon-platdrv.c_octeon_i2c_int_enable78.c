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
struct octeon_i2c {int /*<<< orphan*/  irq; int /*<<< orphan*/  int_enable_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_i2c_int_enable78(struct octeon_i2c *i2c)
{
	atomic_inc_return(&i2c->int_enable_cnt);
	enable_irq(i2c->irq);
}