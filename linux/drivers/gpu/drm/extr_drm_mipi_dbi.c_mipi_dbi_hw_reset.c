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
struct mipi_dbi {int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void mipi_dbi_hw_reset(struct mipi_dbi *dbi)
{
	if (!dbi->reset)
		return;

	gpiod_set_value_cansleep(dbi->reset, 0);
	usleep_range(20, 1000);
	gpiod_set_value_cansleep(dbi->reset, 1);
	msleep(120);
}