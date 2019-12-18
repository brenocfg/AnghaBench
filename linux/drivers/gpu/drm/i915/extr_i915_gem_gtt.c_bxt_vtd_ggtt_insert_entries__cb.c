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
struct insert_entries {int /*<<< orphan*/  vm; int /*<<< orphan*/  flags; int /*<<< orphan*/  level; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_vtd_ggtt_wa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_ggtt_insert_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bxt_vtd_ggtt_insert_entries__cb(void *_arg)
{
	struct insert_entries *arg = _arg;

	gen8_ggtt_insert_entries(arg->vm, arg->vma, arg->level, arg->flags);
	bxt_vtd_ggtt_wa(arg->vm);

	return 0;
}