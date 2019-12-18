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
struct mutex {int dummy; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hex2bitmap (char const*,unsigned long*,int) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 unsigned long* kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,unsigned long) ; 
 int modify_bitmap (char const*,unsigned long*,int) ; 
 scalar_t__ mutex_lock_interruptible (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 

int ap_parse_mask_str(const char *str,
		      unsigned long *bitmap, int bits,
		      struct mutex *lock)
{
	unsigned long *newmap, size;
	int rc;

	/* bits needs to be a multiple of 8 */
	if (bits & 0x07)
		return -EINVAL;

	size = BITS_TO_LONGS(bits)*sizeof(unsigned long);
	newmap = kmalloc(size, GFP_KERNEL);
	if (!newmap)
		return -ENOMEM;
	if (mutex_lock_interruptible(lock)) {
		kfree(newmap);
		return -ERESTARTSYS;
	}

	if (*str == '+' || *str == '-') {
		memcpy(newmap, bitmap, size);
		rc = modify_bitmap(str, newmap, bits);
	} else {
		memset(newmap, 0, size);
		rc = hex2bitmap(str, newmap, bits);
	}
	if (rc == 0)
		memcpy(bitmap, newmap, size);
	mutex_unlock(lock);
	kfree(newmap);
	return rc;
}