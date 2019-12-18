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
typedef  int /*<<< orphan*/  u64 ;
struct rapl_package {int nr_domains; TYPE_3__* domains; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * primitives; } ;
struct TYPE_6__ {TYPE_1__ rdd; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int NR_RAW_PRIMITIVES ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rapl_read_data_raw (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* rpi ; 

__attribute__((used)) static void rapl_update_domain_data(struct rapl_package *rp)
{
	int dmn, prim;
	u64 val;

	for (dmn = 0; dmn < rp->nr_domains; dmn++) {
		pr_debug("update %s domain %s data\n", rp->name,
			 rp->domains[dmn].name);
		/* exclude non-raw primitives */
		for (prim = 0; prim < NR_RAW_PRIMITIVES; prim++) {
			if (!rapl_read_data_raw(&rp->domains[dmn], prim,
						rpi[prim].unit, &val))
				rp->domains[dmn].rdd.primitives[prim] = val;
		}
	}

}