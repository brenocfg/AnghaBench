#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long dss_clk_rate; int /*<<< orphan*/  dss_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,unsigned long) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned long,unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ dss ; 

int dss_set_fck_rate(unsigned long rate)
{
	int r;

	DSSDBG("set fck to %lu\n", rate);

	r = clk_set_rate(dss.dss_clk, rate);
	if (r)
		return r;

	dss.dss_clk_rate = clk_get_rate(dss.dss_clk);

	WARN_ONCE(dss.dss_clk_rate != rate,
			"clk rate mismatch: %lu != %lu", dss.dss_clk_rate,
			rate);

	return 0;
}