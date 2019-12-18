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
struct path_selector_type {int dummy; } ;
struct ps_internal {struct path_selector_type pst; } ;

/* Variables and functions */
 struct ps_internal* get_path_selector (char const*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 

struct path_selector_type *dm_get_path_selector(const char *name)
{
	struct ps_internal *psi;

	if (!name)
		return NULL;

	psi = get_path_selector(name);
	if (!psi) {
		request_module("dm-%s", name);
		psi = get_path_selector(name);
	}

	return psi ? &psi->pst : NULL;
}