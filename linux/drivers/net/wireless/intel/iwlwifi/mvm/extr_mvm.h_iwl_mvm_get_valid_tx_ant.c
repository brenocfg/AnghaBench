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
typedef  int u8 ;
struct iwl_mvm {TYPE_2__* fw; TYPE_1__* nvm_data; } ;
struct TYPE_4__ {int valid_tx_ant; } ;
struct TYPE_3__ {int valid_tx_ant; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 iwl_mvm_get_valid_tx_ant(struct iwl_mvm *mvm)
{
	return mvm->nvm_data && mvm->nvm_data->valid_tx_ant ?
	       mvm->fw->valid_tx_ant & mvm->nvm_data->valid_tx_ant :
	       mvm->fw->valid_tx_ant;
}