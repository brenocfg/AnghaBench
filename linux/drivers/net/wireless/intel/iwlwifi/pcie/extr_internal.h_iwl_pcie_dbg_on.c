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
struct TYPE_2__ {scalar_t__ dest_tlv; } ;
struct iwl_trans {TYPE_1__ dbg; } ;

/* Variables and functions */
 scalar_t__ iwl_trans_dbg_ini_valid (struct iwl_trans*) ; 

__attribute__((used)) static inline bool iwl_pcie_dbg_on(struct iwl_trans *trans)
{
	return (trans->dbg.dest_tlv || iwl_trans_dbg_ini_valid(trans));
}