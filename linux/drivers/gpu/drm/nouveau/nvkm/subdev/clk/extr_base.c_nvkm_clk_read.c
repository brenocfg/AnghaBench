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
struct nvkm_clk {TYPE_1__* func; } ;
typedef  enum nv_clk_src { ____Placeholder_nv_clk_src } nv_clk_src ;
struct TYPE_2__ {int (* read ) (struct nvkm_clk*,int) ;} ;

/* Variables and functions */
 int stub1 (struct nvkm_clk*,int) ; 

int
nvkm_clk_read(struct nvkm_clk *clk, enum nv_clk_src src)
{
	return clk->func->read(clk, src);
}