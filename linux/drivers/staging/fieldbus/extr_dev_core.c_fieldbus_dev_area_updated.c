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
struct fieldbus_dev {int /*<<< orphan*/  dc_wq; int /*<<< orphan*/  dc_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void fieldbus_dev_area_updated(struct fieldbus_dev *fb)
{
	fb->dc_event++;
	wake_up_all(&fb->dc_wq);
}