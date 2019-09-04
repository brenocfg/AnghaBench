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
struct rftype {unsigned long fflags; int /*<<< orphan*/  name; } ;
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rftype*) ; 
 int /*<<< orphan*/  kernfs_remove_by_name (struct kernfs_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int rdtgroup_add_file (struct kernfs_node*,struct rftype*) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 struct rftype* res_common_files ; 

__attribute__((used)) static int rdtgroup_add_files(struct kernfs_node *kn, unsigned long fflags)
{
	struct rftype *rfts, *rft;
	int ret, len;

	rfts = res_common_files;
	len = ARRAY_SIZE(res_common_files);

	lockdep_assert_held(&rdtgroup_mutex);

	for (rft = rfts; rft < rfts + len; rft++) {
		if ((fflags & rft->fflags) == rft->fflags) {
			ret = rdtgroup_add_file(kn, rft);
			if (ret)
				goto error;
		}
	}

	return 0;
error:
	pr_warn("Failed to add %s, err=%d\n", rft->name, ret);
	while (--rft >= rfts) {
		if ((fflags & rft->fflags) == rft->fflags)
			kernfs_remove_by_name(kn, rft->name);
	}
	return ret;
}