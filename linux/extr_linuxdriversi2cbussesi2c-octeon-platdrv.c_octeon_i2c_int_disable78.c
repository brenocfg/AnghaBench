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
 int /*<<< orphan*/  __octeon_i2c_irq_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_i2c_int_disable78(struct octeon_i2c *i2c)
{
	__octeon_i2c_irq_disable(&i2c->int_enable_cnt, i2c->irq);
}