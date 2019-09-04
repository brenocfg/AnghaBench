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
typedef  scalar_t__ u32 ;
struct xgene_enet_pdata {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void xgene_enet_wr_clkrst_csr(struct xgene_enet_pdata *p, u32 offset,
				     u32 val)
{
	iowrite32(val, p->base_addr + offset);
}