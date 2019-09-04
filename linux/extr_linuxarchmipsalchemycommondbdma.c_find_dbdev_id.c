#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ dev_id; } ;
typedef  TYPE_1__ dbdev_tab_t ;

/* Variables and functions */
 int DBDEV_TAB_SIZE ; 
 TYPE_1__* dbdev_tab ; 

__attribute__((used)) static dbdev_tab_t *find_dbdev_id(u32 id)
{
	int i;
	dbdev_tab_t *p;
	for (i = 0; i < DBDEV_TAB_SIZE; ++i) {
		p = &dbdev_tab[i];
		if (p->dev_id == id)
			return p;
	}
	return NULL;
}