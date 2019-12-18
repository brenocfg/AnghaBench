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
struct dm_arg_set {int dummy; } ;
struct cache_args {scalar_t__ origin_sectors; TYPE_1__* ti; int /*<<< orphan*/  origin_dev; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  at_least_one_arg (struct dm_arg_set*,char**) ; 
 int dm_get_device (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_shift_arg (struct dm_arg_set*) ; 
 scalar_t__ get_dev_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_origin_dev(struct cache_args *ca, struct dm_arg_set *as,
			    char **error)
{
	int r;

	if (!at_least_one_arg(as, error))
		return -EINVAL;

	r = dm_get_device(ca->ti, dm_shift_arg(as), FMODE_READ | FMODE_WRITE,
			  &ca->origin_dev);
	if (r) {
		*error = "Error opening origin device";
		return r;
	}

	ca->origin_sectors = get_dev_size(ca->origin_dev);
	if (ca->ti->len > ca->origin_sectors) {
		*error = "Device size larger than cached device";
		return -EINVAL;
	}

	return 0;
}