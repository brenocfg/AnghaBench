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
typedef  int /*<<< orphan*/  u64 ;
struct drm_mm_node {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  div64_u64_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 misalignment(struct drm_mm_node *node, u64 alignment)
{
	u64 rem;

	if (!alignment)
		return 0;

	div64_u64_rem(node->start, alignment, &rem);
	return rem;
}