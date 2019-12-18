#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SIS_OH {TYPE_2__* poh_prev; TYPE_1__* poh_next; } ;
struct TYPE_4__ {TYPE_1__* poh_next; } ;
struct TYPE_3__ {TYPE_2__* poh_prev; } ;

/* Variables and functions */

__attribute__((used)) static void
sisfb_delete_node(struct SIS_OH *poh)
{
	poh->poh_prev->poh_next = poh->poh_next;
	poh->poh_next->poh_prev = poh->poh_prev;
}