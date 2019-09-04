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
struct ts_nbus {int /*<<< orphan*/  strobe; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ts_nbus_start_transaction(struct ts_nbus *ts_nbus)
{
	gpiod_set_value_cansleep(ts_nbus->strobe, 1);
}