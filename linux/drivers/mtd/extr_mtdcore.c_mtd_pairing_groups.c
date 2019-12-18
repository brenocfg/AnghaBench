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
struct mtd_info {TYPE_1__* pairing; } ;
struct TYPE_2__ {int ngroups; } ;

/* Variables and functions */

int mtd_pairing_groups(struct mtd_info *mtd)
{
	if (!mtd->pairing || !mtd->pairing->ngroups)
		return 1;

	return mtd->pairing->ngroups;
}