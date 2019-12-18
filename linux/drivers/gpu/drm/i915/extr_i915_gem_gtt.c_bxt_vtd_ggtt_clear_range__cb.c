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
struct clear_range {int /*<<< orphan*/  vm; int /*<<< orphan*/  length; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_vtd_ggtt_wa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_ggtt_clear_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bxt_vtd_ggtt_clear_range__cb(void *_arg)
{
	struct clear_range *arg = _arg;

	gen8_ggtt_clear_range(arg->vm, arg->start, arg->length);
	bxt_vtd_ggtt_wa(arg->vm);

	return 0;
}