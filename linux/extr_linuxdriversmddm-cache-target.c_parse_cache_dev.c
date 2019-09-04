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
struct dm_arg_set {int dummy; } ;
struct cache_args {int /*<<< orphan*/  cache_dev; int /*<<< orphan*/  cache_sectors; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  at_least_one_arg (struct dm_arg_set*,char**) ; 
 int dm_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_shift_arg (struct dm_arg_set*) ; 
 int /*<<< orphan*/  get_dev_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_cache_dev(struct cache_args *ca, struct dm_arg_set *as,
			   char **error)
{
	int r;

	if (!at_least_one_arg(as, error))
		return -EINVAL;

	r = dm_get_device(ca->ti, dm_shift_arg(as), FMODE_READ | FMODE_WRITE,
			  &ca->cache_dev);
	if (r) {
		*error = "Error opening cache device";
		return r;
	}
	ca->cache_sectors = get_dev_size(ca->cache_dev);

	return 0;
}