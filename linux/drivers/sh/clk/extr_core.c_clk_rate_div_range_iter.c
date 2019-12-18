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
struct clk_rate_round_data {int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long clk_rate_div_range_iter(unsigned int pos,
				    struct clk_rate_round_data *rounder)
{
	return clk_get_rate(rounder->arg) / pos;
}