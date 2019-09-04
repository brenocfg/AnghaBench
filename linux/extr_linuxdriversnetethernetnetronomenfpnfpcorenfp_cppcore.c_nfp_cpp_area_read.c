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
struct TYPE_4__ {TYPE_1__* op; } ;
struct TYPE_3__ {int (* area_read ) (struct nfp_cpp_area*,void*,unsigned long,size_t) ;} ;

/* Variables and functions */
 int stub1 (struct nfp_cpp_area*,void*,unsigned long,size_t) ; 

int nfp_cpp_area_read(struct nfp_cpp_area *area,
		      unsigned long offset, void *kernel_vaddr,
		      size_t length)
{
	return area->cpp->op->area_read(area, kernel_vaddr, offset, length);
}