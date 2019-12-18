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
struct intel_timeline {scalar_t__ has_initial_breadcrumb; int /*<<< orphan*/  seqno; } ;

/* Variables and functions */

__attribute__((used)) static void timeline_rollback(struct intel_timeline *tl)
{
	tl->seqno -= 1 + tl->has_initial_breadcrumb;
}