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
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;
typedef  enum MXL_HYDRA_FEC_E { ____Placeholder_MXL_HYDRA_FEC_E } MXL_HYDRA_FEC_E ;

/* Variables and functions */
 int FEC_1_2 ; 
 int FEC_2_3 ; 
 int FEC_3_4 ; 
 int FEC_3_5 ; 
 int FEC_4_5 ; 
 int FEC_5_6 ; 
 int FEC_6_7 ; 
 int FEC_7_8 ; 
 int FEC_8_9 ; 
 int FEC_9_10 ; 
 int FEC_NONE ; 
 int MXL_HYDRA_FEC_9_10 ; 

__attribute__((used)) static enum fe_code_rate conv_fec(enum MXL_HYDRA_FEC_E fec)
{
	enum fe_code_rate fec2fec[11] = {
		FEC_NONE, FEC_1_2, FEC_3_5, FEC_2_3,
		FEC_3_4, FEC_4_5, FEC_5_6, FEC_6_7,
		FEC_7_8, FEC_8_9, FEC_9_10
	};

	if (fec > MXL_HYDRA_FEC_9_10)
		return FEC_NONE;
	return fec2fec[fec];
}