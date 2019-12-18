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
struct ionic_lif {TYPE_1__* ionic; } ;
struct TYPE_2__ {int nintrs; int /*<<< orphan*/  intrs; } ;

/* Variables and functions */
 int INTR_INDEX_NOT_ASSIGNED ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ionic_intr_free(struct ionic_lif *lif, int index)
{
	if (index != INTR_INDEX_NOT_ASSIGNED && index < lif->ionic->nintrs)
		clear_bit(index, lif->ionic->intrs);
}