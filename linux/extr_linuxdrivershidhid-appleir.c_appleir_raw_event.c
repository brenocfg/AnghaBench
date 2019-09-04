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
typedef  int u8 ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;
struct appleir {int prev_key_idx; int /*<<< orphan*/  key_up_timer; int /*<<< orphan*/  current_key; int /*<<< orphan*/  lock; int /*<<< orphan*/ * keymap; } ;
typedef  int /*<<< orphan*/  keyrepeat ;
typedef  int /*<<< orphan*/  keydown ;
typedef  int /*<<< orphan*/  flatbattery ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  battery_flat (struct appleir*) ; 
 int get_key (int) ; 
 struct appleir* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  key_down (struct hid_device*,struct appleir*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_up (struct hid_device*,struct appleir*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int appleir_raw_event(struct hid_device *hid, struct hid_report *report,
	 u8 *data, int len)
{
	struct appleir *appleir = hid_get_drvdata(hid);
	static const u8 keydown[] = { 0x25, 0x87, 0xee };
	static const u8 keyrepeat[] = { 0x26, };
	static const u8 flatbattery[] = { 0x25, 0x87, 0xe0 };
	unsigned long flags;

	if (len != 5)
		goto out;

	if (!memcmp(data, keydown, sizeof(keydown))) {
		int index;

		spin_lock_irqsave(&appleir->lock, flags);
		/*
		 * If we already have a key down, take it up before marking
		 * this one down
		 */
		if (appleir->current_key)
			key_up(hid, appleir, appleir->current_key);

		/* Handle dual packet commands */
		if (appleir->prev_key_idx > 0)
			index = appleir->prev_key_idx;
		else
			index = get_key(data[4]);

		if (index >= 0) {
			appleir->current_key = appleir->keymap[index];

			key_down(hid, appleir, appleir->current_key);
			/*
			 * Remote doesn't do key up, either pull them up, in
			 * the test above, or here set a timer which pulls
			 * them up after 1/8 s
			 */
			mod_timer(&appleir->key_up_timer, jiffies + HZ / 8);
			appleir->prev_key_idx = 0;
		} else
			/* Remember key for next packet */
			appleir->prev_key_idx = -index;
		spin_unlock_irqrestore(&appleir->lock, flags);
		goto out;
	}

	appleir->prev_key_idx = 0;

	if (!memcmp(data, keyrepeat, sizeof(keyrepeat))) {
		key_down(hid, appleir, appleir->current_key);
		/*
		 * Remote doesn't do key up, either pull them up, in the test
		 * above, or here set a timer which pulls them up after 1/8 s
		 */
		mod_timer(&appleir->key_up_timer, jiffies + HZ / 8);
		goto out;
	}

	if (!memcmp(data, flatbattery, sizeof(flatbattery))) {
		battery_flat(appleir);
		/* Fall through */
	}

out:
	/* let hidraw and hiddev handle the report */
	return 0;
}