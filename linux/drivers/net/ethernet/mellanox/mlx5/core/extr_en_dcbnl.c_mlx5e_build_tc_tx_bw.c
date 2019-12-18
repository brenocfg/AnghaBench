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
struct ieee_ets {int* tc_tsa; int* tc_tx_bw; } ;

/* Variables and functions */
#define  IEEE_8021QAZ_TSA_ETS 130 
#define  IEEE_8021QAZ_TSA_STRICT 129 
#define  IEEE_8021QAZ_TSA_VENDOR 128 
 int MLX5E_MAX_BW_ALLOC ; 

__attribute__((used)) static void mlx5e_build_tc_tx_bw(struct ieee_ets *ets, u8 *tc_tx_bw,
				 u8 *tc_group, int max_tc)
{
	int bw_for_ets_zero_bw_tc = 0;
	int last_ets_zero_bw_tc = -1;
	int num_ets_zero_bw = 0;
	int i;

	for (i = 0; i <= max_tc; i++) {
		if (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS &&
		    !ets->tc_tx_bw[i]) {
			num_ets_zero_bw++;
			last_ets_zero_bw_tc = i;
		}
	}

	if (num_ets_zero_bw)
		bw_for_ets_zero_bw_tc = MLX5E_MAX_BW_ALLOC / num_ets_zero_bw;

	for (i = 0; i <= max_tc; i++) {
		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_VENDOR:
			tc_tx_bw[i] = MLX5E_MAX_BW_ALLOC;
			break;
		case IEEE_8021QAZ_TSA_STRICT:
			tc_tx_bw[i] = MLX5E_MAX_BW_ALLOC;
			break;
		case IEEE_8021QAZ_TSA_ETS:
			tc_tx_bw[i] = ets->tc_tx_bw[i] ?
				      ets->tc_tx_bw[i] :
				      bw_for_ets_zero_bw_tc;
			break;
		}
	}

	/* Make sure the total bw for ets zero bw group is 100% */
	if (last_ets_zero_bw_tc != -1)
		tc_tx_bw[last_ets_zero_bw_tc] +=
			MLX5E_MAX_BW_ALLOC % num_ets_zero_bw;
}