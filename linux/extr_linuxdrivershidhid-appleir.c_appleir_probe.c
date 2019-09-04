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
struct hid_device_id {int dummy; } ;
struct hid_device {int /*<<< orphan*/  quirks; } ;
struct appleir {int /*<<< orphan*/  key_up_timer; int /*<<< orphan*/  lock; struct hid_device* hid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HID_CONNECT_DEFAULT ; 
 int HID_CONNECT_HIDDEV_FORCE ; 
 int /*<<< orphan*/  HID_QUIRK_HIDINPUT_FORCE ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct appleir*) ; 
 int /*<<< orphan*/  key_up_tick ; 
 int /*<<< orphan*/  kfree (struct appleir*) ; 
 struct appleir* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int appleir_probe(struct hid_device *hid, const struct hid_device_id *id)
{
	int ret;
	struct appleir *appleir;

	appleir = kzalloc(sizeof(struct appleir), GFP_KERNEL);
	if (!appleir) {
		ret = -ENOMEM;
		goto allocfail;
	}

	appleir->hid = hid;

	/* force input as some remotes bypass the input registration */
	hid->quirks |= HID_QUIRK_HIDINPUT_FORCE;

	spin_lock_init(&appleir->lock);
	timer_setup(&appleir->key_up_timer, key_up_tick, 0);

	hid_set_drvdata(hid, appleir);

	ret = hid_parse(hid);
	if (ret) {
		hid_err(hid, "parse failed\n");
		goto fail;
	}

	ret = hid_hw_start(hid, HID_CONNECT_DEFAULT | HID_CONNECT_HIDDEV_FORCE);
	if (ret) {
		hid_err(hid, "hw start failed\n");
		goto fail;
	}

	return 0;
fail:
	kfree(appleir);
allocfail:
	return ret;
}