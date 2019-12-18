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
struct mapped_device {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_FREEING ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
 int MINORBITS ; 
 struct mapped_device* MINOR_ALLOCED ; 
 scalar_t__ _major ; 
 int /*<<< orphan*/  _minor_idr ; 
 int /*<<< orphan*/  _minor_lock ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_deleting_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_get (struct mapped_device*) ; 
 struct mapped_device* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct mapped_device *dm_get_md(dev_t dev)
{
	struct mapped_device *md;
	unsigned minor = MINOR(dev);

	if (MAJOR(dev) != _major || minor >= (1 << MINORBITS))
		return NULL;

	spin_lock(&_minor_lock);

	md = idr_find(&_minor_idr, minor);
	if (!md || md == MINOR_ALLOCED || (MINOR(disk_devt(dm_disk(md))) != minor) ||
	    test_bit(DMF_FREEING, &md->flags) || dm_deleting_md(md)) {
		md = NULL;
		goto out;
	}
	dm_get(md);
out:
	spin_unlock(&_minor_lock);

	return md;
}