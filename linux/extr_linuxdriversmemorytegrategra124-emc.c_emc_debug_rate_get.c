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
typedef  int /*<<< orphan*/  u64 ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 

__attribute__((used)) static int emc_debug_rate_get(void *data, u64 *rate)
{
	struct clk *c = data;

	*rate = clk_get_rate(c);

	return 0;
}