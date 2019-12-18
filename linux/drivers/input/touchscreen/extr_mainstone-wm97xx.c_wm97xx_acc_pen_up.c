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
struct wm97xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODR ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static void wm97xx_acc_pen_up(struct wm97xx *wm)
{
	unsigned int count;

	schedule_timeout_uninterruptible(1);

	for (count = 0; count < 16; count++)
		MODR;
}