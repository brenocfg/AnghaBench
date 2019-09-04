#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vr_nor_mtd {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int mtd_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vr_nor_init_partitions(struct vr_nor_mtd *p)
{
	/* register the flash bank */
	/* partition the flash bank */
	return mtd_device_register(p->info, NULL, 0);
}