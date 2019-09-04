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
struct loop_device {int lo_number; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  find_free_cb ; 
 struct loop_device* idr_find (int /*<<< orphan*/ *,int) ; 
 int idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct loop_device**) ; 
 int /*<<< orphan*/  loop_index_idr ; 

__attribute__((used)) static int loop_lookup(struct loop_device **l, int i)
{
	struct loop_device *lo;
	int ret = -ENODEV;

	if (i < 0) {
		int err;

		err = idr_for_each(&loop_index_idr, &find_free_cb, &lo);
		if (err == 1) {
			*l = lo;
			ret = lo->lo_number;
		}
		goto out;
	}

	/* lookup and return a specific i */
	lo = idr_find(&loop_index_idr, i);
	if (lo) {
		*l = lo;
		ret = lo->lo_number;
	}
out:
	return ret;
}