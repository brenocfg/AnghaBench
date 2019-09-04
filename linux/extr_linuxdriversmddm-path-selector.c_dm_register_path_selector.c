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
struct ps_internal {int /*<<< orphan*/  list; } ;
struct path_selector_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 scalar_t__ __find_path_selector_type (int /*<<< orphan*/ ) ; 
 struct ps_internal* _alloc_path_selector (struct path_selector_type*) ; 
 int /*<<< orphan*/  _path_selectors ; 
 int /*<<< orphan*/  _ps_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ps_internal*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_register_path_selector(struct path_selector_type *pst)
{
	int r = 0;
	struct ps_internal *psi = _alloc_path_selector(pst);

	if (!psi)
		return -ENOMEM;

	down_write(&_ps_lock);

	if (__find_path_selector_type(pst->name)) {
		kfree(psi);
		r = -EEXIST;
	} else
		list_add(&psi->list, &_path_selectors);

	up_write(&_ps_lock);

	return r;
}