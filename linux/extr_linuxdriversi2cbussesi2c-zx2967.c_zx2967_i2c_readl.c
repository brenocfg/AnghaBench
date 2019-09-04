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
typedef  int /*<<< orphan*/  u32 ;
struct zx2967_i2c {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 zx2967_i2c_readl(struct zx2967_i2c *i2c, unsigned long reg)
{
	return readl_relaxed(i2c->reg_base + reg);
}