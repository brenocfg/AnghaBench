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
struct cmhid {int dummy; } ;

/* Variables and functions */
 struct cmhid* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct cmhid*) ; 

__attribute__((used)) static void cmhid_remove(struct hid_device *hid)
{
	struct cmhid *cm = hid_get_drvdata(hid);

	hid_hw_stop(hid);
	kfree(cm);
}