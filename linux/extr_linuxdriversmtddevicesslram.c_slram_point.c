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
struct mtd_info {TYPE_1__* priv; } ;
struct TYPE_2__ {void* start; } ;
typedef  TYPE_1__ slram_priv_t ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int loff_t ;

/* Variables and functions */

__attribute__((used)) static int slram_point(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, void **virt, resource_size_t *phys)
{
	slram_priv_t *priv = mtd->priv;

	*virt = priv->start + from;
	*retlen = len;
	return(0);
}