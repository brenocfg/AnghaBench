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
typedef  enum ath10k_amsdu_subfrm_num { ____Placeholder_ath10k_amsdu_subfrm_num } ath10k_amsdu_subfrm_num ;

/* Variables and functions */
#define  ATH10K_AMSDU_SUBFRM_NUM_1 133 
#define  ATH10K_AMSDU_SUBFRM_NUM_2 132 
#define  ATH10K_AMSDU_SUBFRM_NUM_3 131 
#define  ATH10K_AMSDU_SUBFRM_NUM_4 130 
#define  ATH10K_AMSDU_SUBFRM_NUM_MAX 129 
#define  ATH10K_AMSDU_SUBFRM_NUM_MORE 128 

__attribute__((used)) static char *get_num_amsdu_subfrm_str(enum ath10k_amsdu_subfrm_num i)
{
	switch (i) {
	case ATH10K_AMSDU_SUBFRM_NUM_1:
		return "1";
	case ATH10K_AMSDU_SUBFRM_NUM_2:
		return "2";
	case ATH10K_AMSDU_SUBFRM_NUM_3:
		return "3";
	case ATH10K_AMSDU_SUBFRM_NUM_4:
		return "4";
	case ATH10K_AMSDU_SUBFRM_NUM_MORE:
		return ">4";
	case ATH10K_AMSDU_SUBFRM_NUM_MAX:
		return "0";
	}

	return "0";
}