#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vr_nor_mtd {TYPE_2__* dev; TYPE_3__* info; int /*<<< orphan*/  map; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_3__* do_map_probe (char const* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vr_nor_mtd_setup(struct vr_nor_mtd *p)
{
	static const char * const probe_types[] =
	    { "cfi_probe", "jedec_probe", NULL };
	const char * const *type;

	for (type = probe_types; !p->info && *type; type++)
		p->info = do_map_probe(*type, &p->map);
	if (!p->info)
		return -ENODEV;

	p->info->dev.parent = &p->dev->dev;

	return 0;
}