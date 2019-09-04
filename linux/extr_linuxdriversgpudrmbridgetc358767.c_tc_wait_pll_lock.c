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
struct tc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tc_wait_pll_lock(struct tc_data *tc)
{
	/* Wait for PLL to lock: up to 2.09 ms, depending on refclk */
	usleep_range(3000, 6000);
}