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
struct uverbs_api_object {int dummy; } ;
struct ib_uverbs_file {int dummy; } ;
struct ib_uobject {int id; struct ib_uverbs_file* ufile; } ;

/* Variables and functions */
 struct ib_uobject* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ib_uobject*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 struct ib_uobject* alloc_uobj (struct ib_uverbs_file*,struct uverbs_api_object const*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 

__attribute__((used)) static struct ib_uobject *
alloc_begin_fd_uobject(const struct uverbs_api_object *obj,
		       struct ib_uverbs_file *ufile)
{
	int new_fd;
	struct ib_uobject *uobj;

	new_fd = get_unused_fd_flags(O_CLOEXEC);
	if (new_fd < 0)
		return ERR_PTR(new_fd);

	uobj = alloc_uobj(ufile, obj);
	if (IS_ERR(uobj)) {
		put_unused_fd(new_fd);
		return uobj;
	}

	uobj->id = new_fd;
	uobj->ufile = ufile;

	return uobj;
}