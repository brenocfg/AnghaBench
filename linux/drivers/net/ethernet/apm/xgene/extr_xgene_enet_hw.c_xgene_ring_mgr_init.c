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
struct xgene_enet_pdata {scalar_t__ ring_csr_addr; } ;

/* Variables and functions */
 scalar_t__ CLKEN_ADDR ; 
 scalar_t__ SRST_ADDR ; 
 scalar_t__ ioread32 (scalar_t__) ; 

bool xgene_ring_mgr_init(struct xgene_enet_pdata *p)
{
	if (!ioread32(p->ring_csr_addr + CLKEN_ADDR))
		return false;

	if (ioread32(p->ring_csr_addr + SRST_ADDR))
		return false;

	return true;
}