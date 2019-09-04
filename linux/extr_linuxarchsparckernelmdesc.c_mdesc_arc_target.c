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
typedef  int u64 ;
struct mdesc_handle {int /*<<< orphan*/  mdesc; } ;
struct TYPE_2__ {int val; } ;
struct mdesc_elem {TYPE_1__ d; } ;

/* Variables and functions */
 struct mdesc_elem* node_block (int /*<<< orphan*/ *) ; 

u64 mdesc_arc_target(struct mdesc_handle *hp, u64 arc)
{
	struct mdesc_elem *ep, *base = node_block(&hp->mdesc);

	ep = base + arc;

	return ep->d.val;
}