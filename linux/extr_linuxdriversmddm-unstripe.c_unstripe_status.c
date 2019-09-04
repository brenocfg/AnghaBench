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
struct unstripe_c {scalar_t__ physical_start; TYPE_1__* dev; int /*<<< orphan*/  unstripe; scalar_t__ chunk_size; int /*<<< orphan*/  stripes; } ;
struct dm_target {struct unstripe_c* private; } ;
typedef  int status_type_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static void unstripe_status(struct dm_target *ti, status_type_t type,
			    unsigned int status_flags, char *result, unsigned int maxlen)
{
	struct unstripe_c *uc = ti->private;
	unsigned int sz = 0;

	switch (type) {
	case STATUSTYPE_INFO:
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%d %llu %d %s %llu",
		       uc->stripes, (unsigned long long)uc->chunk_size, uc->unstripe,
		       uc->dev->name, (unsigned long long)uc->physical_start);
		break;
	}
}