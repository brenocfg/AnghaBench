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
typedef  scalar_t__ u32 ;
struct imon_context {int rc_toggle; int release_code; int /*<<< orphan*/  rdev; scalar_t__ rc_scancode; } ;

/* Variables and functions */
 scalar_t__ KEY_RESERVED ; 
 scalar_t__ rc_g_keycode_from_table (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 imon_remote_key_lookup(struct imon_context *ictx, u32 scancode)
{
	u32 keycode;
	u32 release;
	bool is_release_code = false;

	/* Look for the initial press of a button */
	keycode = rc_g_keycode_from_table(ictx->rdev, scancode);
	ictx->rc_toggle = 0x0;
	ictx->rc_scancode = scancode;

	/* Look for the release of a button */
	if (keycode == KEY_RESERVED) {
		release = scancode & ~0x4000;
		keycode = rc_g_keycode_from_table(ictx->rdev, release);
		if (keycode != KEY_RESERVED)
			is_release_code = true;
	}

	ictx->release_code = is_release_code;

	return keycode;
}