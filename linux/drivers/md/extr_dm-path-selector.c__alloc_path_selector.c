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
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ps_internal* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ps_internal *_alloc_path_selector(struct path_selector_type *pst)
{
	struct ps_internal *psi = kzalloc(sizeof(*psi), GFP_KERNEL);

	if (psi)
		psi->pst = *pst;

	return psi;
}