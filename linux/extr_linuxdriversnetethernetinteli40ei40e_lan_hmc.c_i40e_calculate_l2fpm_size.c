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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int I40E_HMC_OBJ_SIZE_FCOE_CNTX ; 
 int I40E_HMC_OBJ_SIZE_FCOE_FILT ; 
 int I40E_HMC_OBJ_SIZE_RXQ ; 
 int I40E_HMC_OBJ_SIZE_TXQ ; 
 int i40e_align_l2obj_base (int) ; 

__attribute__((used)) static u64 i40e_calculate_l2fpm_size(u32 txq_num, u32 rxq_num,
			      u32 fcoe_cntx_num, u32 fcoe_filt_num)
{
	u64 fpm_size = 0;

	fpm_size = txq_num * I40E_HMC_OBJ_SIZE_TXQ;
	fpm_size = i40e_align_l2obj_base(fpm_size);

	fpm_size += (rxq_num * I40E_HMC_OBJ_SIZE_RXQ);
	fpm_size = i40e_align_l2obj_base(fpm_size);

	fpm_size += (fcoe_cntx_num * I40E_HMC_OBJ_SIZE_FCOE_CNTX);
	fpm_size = i40e_align_l2obj_base(fpm_size);

	fpm_size += (fcoe_filt_num * I40E_HMC_OBJ_SIZE_FCOE_FILT);
	fpm_size = i40e_align_l2obj_base(fpm_size);

	return fpm_size;
}