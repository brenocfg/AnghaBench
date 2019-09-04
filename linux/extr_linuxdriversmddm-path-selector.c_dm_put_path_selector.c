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
struct TYPE_2__ {int /*<<< orphan*/  module; } ;
struct ps_internal {TYPE_1__ pst; } ;
struct path_selector_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct ps_internal* __find_path_selector_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ps_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void dm_put_path_selector(struct path_selector_type *pst)
{
	struct ps_internal *psi;

	if (!pst)
		return;

	down_read(&_ps_lock);
	psi = __find_path_selector_type(pst->name);
	if (!psi)
		goto out;

	module_put(psi->pst.module);
out:
	up_read(&_ps_lock);
}