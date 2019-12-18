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
struct rvt_qpn_table {TYPE_1__* map; } ;
struct TYPE_2__ {scalar_t__ page; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void free_qpn_table(struct rvt_qpn_table *qpt)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(qpt->map); i++)
		free_page((unsigned long)qpt->map[i].page);
}