#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ plci; struct TYPE_5__* next; } ;
typedef  TYPE_1__ capidrv_plci ;
struct TYPE_6__ {TYPE_1__* plci_list; } ;
typedef  TYPE_2__ capidrv_contr ;

/* Variables and functions */

__attribute__((used)) static capidrv_plci *find_plci_by_plci(capidrv_contr *card, u32 plci)
{
	capidrv_plci *p;
	for (p = card->plci_list; p; p = p->next)
		if (p->plci == plci)
			return p;
	return NULL;
}