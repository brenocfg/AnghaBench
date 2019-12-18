#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_arg_set {int dummy; } ;
struct clone {int /*<<< orphan*/  source_dev; TYPE_1__* ti; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int dm_get_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_put_device (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_shift_arg (struct dm_arg_set*) ; 
 scalar_t__ get_dev_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_source_dev(struct clone *clone, struct dm_arg_set *as, char **error)
{
	int r;
	sector_t source_dev_size;

	r = dm_get_device(clone->ti, dm_shift_arg(as), FMODE_READ,
			  &clone->source_dev);
	if (r) {
		*error = "Error opening source device";
		return r;
	}

	source_dev_size = get_dev_size(clone->source_dev);
	if (source_dev_size < clone->ti->len) {
		dm_put_device(clone->ti, clone->source_dev);
		*error = "Device size larger than source device";
		return -EINVAL;
	}

	return 0;
}