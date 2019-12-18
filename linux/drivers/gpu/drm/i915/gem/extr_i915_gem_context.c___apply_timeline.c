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
struct intel_context {int /*<<< orphan*/  timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_timeline (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void __apply_timeline(struct intel_context *ce, void *timeline)
{
	__set_timeline(&ce->timeline, timeline);
}