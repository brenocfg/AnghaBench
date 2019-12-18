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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_STATE_ADDR ; 
 int /*<<< orphan*/  BACKLIGHT_STATE_OFF_DATA ; 
 int /*<<< orphan*/  BACKLIGHT_STATE_ON_DATA ; 
 int /*<<< orphan*/  ec_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_backlight_state(bool on)
{
	u8 data = on ? BACKLIGHT_STATE_ON_DATA : BACKLIGHT_STATE_OFF_DATA;
	ec_transaction(BACKLIGHT_STATE_ADDR, &data, 1, NULL, 0);
}