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

/* Variables and functions */
 struct ps_internal* __find_path_selector_type (char const*) ; 
 int /*<<< orphan*/  _ps_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ps_internal *get_path_selector(const char *name)
{
	struct ps_internal *psi;

	down_read(&_ps_lock);
	psi = __find_path_selector_type(name);
	if (psi && !try_module_get(psi->pst.module))
		psi = NULL;
	up_read(&_ps_lock);

	return psi;
}