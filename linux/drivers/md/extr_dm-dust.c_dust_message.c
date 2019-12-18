#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dust_device {int fail_read_on_bb; int quiet_mode; int /*<<< orphan*/  sect_per_block; int /*<<< orphan*/  dust_lock; int /*<<< orphan*/  badblock_count; TYPE_2__* dev; } ;
struct dm_target {struct dust_device* private; } ;
typedef  unsigned long long sector_t ;
struct TYPE_4__ {TYPE_1__* bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int /*<<< orphan*/  DMINFO (char*,...) ; 
 int EINVAL ; 
 unsigned long long SECTOR_SHIFT ; 
 int dust_add_block (struct dust_device*,unsigned long long) ; 
 int dust_clear_badblocks (struct dust_device*) ; 
 int dust_query_block (struct dust_device*,unsigned long long) ; 
 int dust_remove_block (struct dust_device*,unsigned long long) ; 
 unsigned long long i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_div (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sscanf (char*,char*,unsigned long long*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int dust_message(struct dm_target *ti, unsigned int argc, char **argv,
			char *result_buf, unsigned int maxlen)
{
	struct dust_device *dd = ti->private;
	sector_t size = i_size_read(dd->dev->bdev->bd_inode) >> SECTOR_SHIFT;
	bool invalid_msg = false;
	int result = -EINVAL;
	unsigned long long tmp, block;
	unsigned long flags;
	char dummy;

	if (argc == 1) {
		if (!strcasecmp(argv[0], "addbadblock") ||
		    !strcasecmp(argv[0], "removebadblock") ||
		    !strcasecmp(argv[0], "queryblock")) {
			DMERR("%s requires an additional argument", argv[0]);
		} else if (!strcasecmp(argv[0], "disable")) {
			DMINFO("disabling read failures on bad sectors");
			dd->fail_read_on_bb = false;
			result = 0;
		} else if (!strcasecmp(argv[0], "enable")) {
			DMINFO("enabling read failures on bad sectors");
			dd->fail_read_on_bb = true;
			result = 0;
		} else if (!strcasecmp(argv[0], "countbadblocks")) {
			spin_lock_irqsave(&dd->dust_lock, flags);
			DMINFO("countbadblocks: %llu badblock(s) found",
			       dd->badblock_count);
			spin_unlock_irqrestore(&dd->dust_lock, flags);
			result = 0;
		} else if (!strcasecmp(argv[0], "clearbadblocks")) {
			result = dust_clear_badblocks(dd);
		} else if (!strcasecmp(argv[0], "quiet")) {
			if (!dd->quiet_mode)
				dd->quiet_mode = true;
			else
				dd->quiet_mode = false;
			result = 0;
		} else {
			invalid_msg = true;
		}
	} else if (argc == 2) {
		if (sscanf(argv[1], "%llu%c", &tmp, &dummy) != 1)
			return result;

		block = tmp;
		sector_div(size, dd->sect_per_block);
		if (block > size) {
			DMERR("selected block value out of range");
			return result;
		}

		if (!strcasecmp(argv[0], "addbadblock"))
			result = dust_add_block(dd, block);
		else if (!strcasecmp(argv[0], "removebadblock"))
			result = dust_remove_block(dd, block);
		else if (!strcasecmp(argv[0], "queryblock"))
			result = dust_query_block(dd, block);
		else
			invalid_msg = true;

	} else
		DMERR("invalid number of arguments '%d'", argc);

	if (invalid_msg)
		DMERR("unrecognized message '%s' received", argv[0]);

	return result;
}