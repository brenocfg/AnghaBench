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
struct bu21029_ts_data {scalar_t__ reset_gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  STOP_DELAY_MAX_US ; 
 int /*<<< orphan*/  STOP_DELAY_MIN_US ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bu21029_put_chip_in_reset(struct bu21029_ts_data *bu21029)
{
	if (bu21029->reset_gpios) {
		gpiod_set_value_cansleep(bu21029->reset_gpios, 1);
		usleep_range(STOP_DELAY_MIN_US, STOP_DELAY_MAX_US);
	}
}