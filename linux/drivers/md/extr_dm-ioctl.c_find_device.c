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
struct mapped_device {int dummy; } ;
struct hash_cell {struct mapped_device* md; } ;
struct dm_ioctl {int dummy; } ;

/* Variables and functions */
 struct hash_cell* __find_device_hash_cell (struct dm_ioctl*) ; 
 int /*<<< orphan*/  _hash_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mapped_device *find_device(struct dm_ioctl *param)
{
	struct hash_cell *hc;
	struct mapped_device *md = NULL;

	down_read(&_hash_lock);
	hc = __find_device_hash_cell(param);
	if (hc)
		md = hc->md;
	up_read(&_hash_lock);

	return md;
}