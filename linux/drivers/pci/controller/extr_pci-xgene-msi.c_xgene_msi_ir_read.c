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
typedef  int u32 ;
struct xgene_msi {scalar_t__ msi_regs; } ;

/* Variables and functions */
 scalar_t__ MSI_IR0 ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 xgene_msi_ir_read(struct xgene_msi *msi,
				    u32 msi_grp, u32 msir_idx)
{
	return readl_relaxed(msi->msi_regs + MSI_IR0 +
			      (msi_grp << 19) + (msir_idx << 16));
}