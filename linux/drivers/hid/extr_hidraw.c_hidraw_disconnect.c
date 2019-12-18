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
struct hidraw {int dummy; } ;
struct hid_device {struct hidraw* hidraw; } ;

/* Variables and functions */
 int /*<<< orphan*/  drop_ref (struct hidraw*,int) ; 
 int /*<<< orphan*/  minors_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void hidraw_disconnect(struct hid_device *hid)
{
	struct hidraw *hidraw = hid->hidraw;

	mutex_lock(&minors_lock);

	drop_ref(hidraw, 1);

	mutex_unlock(&minors_lock);
}