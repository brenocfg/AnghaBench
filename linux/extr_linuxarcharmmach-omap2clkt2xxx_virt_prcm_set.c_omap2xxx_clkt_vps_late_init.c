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
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  sys_ck_rate ; 

void omap2xxx_clkt_vps_late_init(void)
{
	struct clk *c;

	c = clk_get(NULL, "sys_ck");
	if (IS_ERR(c)) {
		WARN(1, "could not locate sys_ck\n");
	} else {
		sys_ck_rate = clk_get_rate(c);
		clk_put(c);
	}
}