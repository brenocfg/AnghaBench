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
struct nfp_cpp_area {TYPE_2__* cpp; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_4__ {TYPE_1__* op; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* area_phys ) (struct nfp_cpp_area*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfp_cpp_area*) ; 

phys_addr_t nfp_cpp_area_phys(struct nfp_cpp_area *area)
{
	phys_addr_t addr = ~0;

	if (area->cpp->op->area_phys)
		addr = area->cpp->op->area_phys(area);

	return addr;
}