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
struct lp855x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8557_BL_CMD ; 
 int /*<<< orphan*/  LP8557_BL_MASK ; 
 int /*<<< orphan*/  LP8557_BL_OFF ; 
 int lp855x_update_bit (struct lp855x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp8557_bl_off(struct lp855x *lp)
{
	/* BL_ON = 0 before updating EPROM settings */
	return lp855x_update_bit(lp, LP8557_BL_CMD, LP8557_BL_MASK,
				LP8557_BL_OFF);
}