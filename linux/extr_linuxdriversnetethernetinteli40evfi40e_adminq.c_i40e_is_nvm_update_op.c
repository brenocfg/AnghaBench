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
struct i40e_aq_desc {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ i40e_aqc_opc_nvm_erase ; 
 scalar_t__ i40e_aqc_opc_nvm_update ; 

__attribute__((used)) static inline bool i40e_is_nvm_update_op(struct i40e_aq_desc *desc)
{
	return (desc->opcode == i40e_aqc_opc_nvm_erase) ||
	       (desc->opcode == i40e_aqc_opc_nvm_update);
}