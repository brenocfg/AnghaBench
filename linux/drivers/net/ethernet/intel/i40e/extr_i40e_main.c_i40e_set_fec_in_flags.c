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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int I40E_AQ_SET_FEC_ABILITY_KR ; 
 int I40E_AQ_SET_FEC_ABILITY_RS ; 
 int I40E_AQ_SET_FEC_AUTO ; 
 int I40E_AQ_SET_FEC_REQUEST_KR ; 
 int I40E_AQ_SET_FEC_REQUEST_RS ; 
 int I40E_FLAG_BASE_R_FEC ; 
 int I40E_FLAG_RS_FEC ; 

void i40e_set_fec_in_flags(u8 fec_cfg, u32 *flags)
{
	if (fec_cfg & I40E_AQ_SET_FEC_AUTO)
		*flags |= I40E_FLAG_RS_FEC | I40E_FLAG_BASE_R_FEC;
	if ((fec_cfg & I40E_AQ_SET_FEC_REQUEST_RS) ||
	    (fec_cfg & I40E_AQ_SET_FEC_ABILITY_RS)) {
		*flags |= I40E_FLAG_RS_FEC;
		*flags &= ~I40E_FLAG_BASE_R_FEC;
	}
	if ((fec_cfg & I40E_AQ_SET_FEC_REQUEST_KR) ||
	    (fec_cfg & I40E_AQ_SET_FEC_ABILITY_KR)) {
		*flags |= I40E_FLAG_BASE_R_FEC;
		*flags &= ~I40E_FLAG_RS_FEC;
	}
	if (fec_cfg == 0)
		*flags &= ~(I40E_FLAG_RS_FEC | I40E_FLAG_BASE_R_FEC);
}