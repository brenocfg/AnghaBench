#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dust_device {int /*<<< orphan*/  blksz; scalar_t__ start; TYPE_1__* dev; int /*<<< orphan*/  quiet_mode; int /*<<< orphan*/  fail_read_on_bb; } ;
struct dm_target {struct dust_device* private; } ;
typedef  int status_type_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,int /*<<< orphan*/ ,...) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static void dust_status(struct dm_target *ti, status_type_t type,
			unsigned int status_flags, char *result, unsigned int maxlen)
{
	struct dust_device *dd = ti->private;
	unsigned int sz = 0;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%s %s %s", dd->dev->name,
		       dd->fail_read_on_bb ? "fail_read_on_bad_block" : "bypass",
		       dd->quiet_mode ? "quiet" : "verbose");
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%s %llu %u", dd->dev->name,
		       (unsigned long long)dd->start, dd->blksz);
		break;
	}
}