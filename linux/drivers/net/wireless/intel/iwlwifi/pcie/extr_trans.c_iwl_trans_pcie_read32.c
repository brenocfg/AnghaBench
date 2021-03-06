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
typedef  scalar_t__ u32 ;
struct iwl_trans {int dummy; } ;
struct TYPE_2__ {scalar_t__ hw_base; } ;

/* Variables and functions */
 TYPE_1__* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 iwl_trans_pcie_read32(struct iwl_trans *trans, u32 ofs)
{
	return readl(IWL_TRANS_GET_PCIE_TRANS(trans)->hw_base + ofs);
}