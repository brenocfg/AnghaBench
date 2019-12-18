#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct nfp_cpp_area {TYPE_2__* cpp; } ;
struct TYPE_4__ {TYPE_1__* op; } ;
struct TYPE_3__ {struct resource* (* area_resource ) (struct nfp_cpp_area*) ;} ;

/* Variables and functions */
 struct resource* stub1 (struct nfp_cpp_area*) ; 

struct resource *nfp_cpp_area_resource(struct nfp_cpp_area *area)
{
	struct resource *res = NULL;

	if (area->cpp->op->area_resource)
		res = area->cpp->op->area_resource(area);

	return res;
}