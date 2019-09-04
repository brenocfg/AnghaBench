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
typedef  int /*<<< orphan*/  upath ;
typedef  int /*<<< orphan*/  u64 ;
struct sa_path_rec {int dummy; } ;
struct ib_user_path_rec {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ copy_from_user (struct ib_user_path_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_copy_path_rec_from_user (struct sa_path_rec*,struct ib_user_path_rec*) ; 
 int /*<<< orphan*/  kfree (struct sa_path_rec*) ; 
 struct sa_path_rec* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_ucm_path_get(struct sa_path_rec **path, u64 src)
{
	struct ib_user_path_rec upath;
	struct sa_path_rec  *sa_path;

	*path = NULL;

	if (!src)
		return 0;

	sa_path = kmalloc(sizeof(*sa_path), GFP_KERNEL);
	if (!sa_path)
		return -ENOMEM;

	if (copy_from_user(&upath, u64_to_user_ptr(src),
			   sizeof(upath))) {

		kfree(sa_path);
		return -EFAULT;
	}

	ib_copy_path_rec_from_user(sa_path, &upath);
	*path = sa_path;
	return 0;
}