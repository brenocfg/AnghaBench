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
struct mlx4_en_priv {int dummy; } ;
struct ieee_ets {scalar_t__* prio_tc; int* tc_tsa; int* tc_tx_bw; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE_8021QAZ_MAX_TCS ; 
#define  IEEE_8021QAZ_TSA_ETS 130 
#define  IEEE_8021QAZ_TSA_STRICT 129 
#define  IEEE_8021QAZ_TSA_VENDOR 128 
 int MLX4_EN_BW_MAX ; 
 scalar_t__ MLX4_EN_NUM_UP_HIGH ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int,...) ; 

__attribute__((used)) static int mlx4_en_ets_validate(struct mlx4_en_priv *priv, struct ieee_ets *ets)
{
	int i;
	int total_ets_bw = 0;
	int has_ets_tc = 0;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->prio_tc[i] >= MLX4_EN_NUM_UP_HIGH) {
			en_err(priv, "Bad priority in UP <=> TC mapping. TC: %d, UP: %d\n",
					i, ets->prio_tc[i]);
			return -EINVAL;
		}

		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_VENDOR:
		case IEEE_8021QAZ_TSA_STRICT:
			break;
		case IEEE_8021QAZ_TSA_ETS:
			has_ets_tc = 1;
			total_ets_bw += ets->tc_tx_bw[i];
			break;
		default:
			en_err(priv, "TC[%d]: Not supported TSA: %d\n",
					i, ets->tc_tsa[i]);
			return -EOPNOTSUPP;
		}
	}

	if (has_ets_tc && total_ets_bw != MLX4_EN_BW_MAX) {
		en_err(priv, "Bad ETS BW sum: %d. Should be exactly 100%%\n",
				total_ets_bw);
		return -EINVAL;
	}

	return 0;
}