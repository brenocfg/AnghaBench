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
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  umem_pd; } ;

/* Variables and functions */
 TYPE_1__* to_upd (struct ib_pd*) ; 
 int /*<<< orphan*/  usnic_uiom_dealloc_pd (int /*<<< orphan*/ ) ; 

void usnic_ib_dealloc_pd(struct ib_pd *pd, struct ib_udata *udata)
{
	usnic_uiom_dealloc_pd((to_upd(pd))->umem_pd);
}