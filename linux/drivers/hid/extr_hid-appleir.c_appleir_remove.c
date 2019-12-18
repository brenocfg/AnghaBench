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
struct hid_device {int dummy; } ;
struct appleir {int /*<<< orphan*/  key_up_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct appleir* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct appleir*) ; 

__attribute__((used)) static void appleir_remove(struct hid_device *hid)
{
	struct appleir *appleir = hid_get_drvdata(hid);
	hid_hw_stop(hid);
	del_timer_sync(&appleir->key_up_timer);
	kfree(appleir);
}