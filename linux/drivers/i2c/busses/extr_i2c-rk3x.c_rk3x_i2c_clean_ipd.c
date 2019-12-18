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
struct rk3x_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_INT_ALL ; 
 int /*<<< orphan*/  REG_IPD ; 
 int /*<<< orphan*/  i2c_writel (struct rk3x_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rk3x_i2c_clean_ipd(struct rk3x_i2c *i2c)
{
	i2c_writel(i2c, REG_INT_ALL, REG_IPD);
}