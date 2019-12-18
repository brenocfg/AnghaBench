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
typedef  int /*<<< orphan*/  u32 ;
struct execlist_ring_context {TYPE_1__* pdps; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */

__attribute__((used)) static void set_context_pdp_root_pointer(
		struct execlist_ring_context *ring_context,
		u32 pdp[8])
{
	int i;

	for (i = 0; i < 8; i++)
		ring_context->pdps[i].val = pdp[7 - i];
}