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
typedef  int u32 ;
struct intel_timeline {int seqno; int has_initial_breadcrumb; int /*<<< orphan*/  pin_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 timeline_advance(struct intel_timeline *tl)
{
	GEM_BUG_ON(!atomic_read(&tl->pin_count));
	GEM_BUG_ON(tl->seqno & tl->has_initial_breadcrumb);

	return tl->seqno += 1 + tl->has_initial_breadcrumb;
}