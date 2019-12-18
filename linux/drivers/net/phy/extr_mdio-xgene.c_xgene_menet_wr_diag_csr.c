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
struct xgene_mdio_pdata {scalar_t__ diag_csr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void xgene_menet_wr_diag_csr(struct xgene_mdio_pdata *pdata,
				    u32 offset, u32 val)
{
	iowrite32(val, pdata->diag_csr_addr + offset);
}