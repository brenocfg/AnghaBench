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
struct atkbd {int /*<<< orphan*/  force_release_mask; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_KEYMAP_SIZE ; 
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bitmap_parselist (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_mask ; 

__attribute__((used)) static ssize_t atkbd_set_force_release(struct atkbd *atkbd,
					const char *buf, size_t count)
{
	/* 64 bytes on stack should be acceptable */
	DECLARE_BITMAP(new_mask, ATKBD_KEYMAP_SIZE);
	int err;

	err = bitmap_parselist(buf, new_mask, ATKBD_KEYMAP_SIZE);
	if (err)
		return err;

	memcpy(atkbd->force_release_mask, new_mask, sizeof(atkbd->force_release_mask));
	return count;
}