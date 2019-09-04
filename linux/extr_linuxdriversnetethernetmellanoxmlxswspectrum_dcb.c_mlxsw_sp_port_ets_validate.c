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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct net_device* dev; } ;
struct ieee_ets {int* tc_tsa; int* tc_tx_bw; int* prio_tc; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE_8021QAZ_MAX_TCS ; 
#define  IEEE_8021QAZ_TSA_ETS 129 
#define  IEEE_8021QAZ_TSA_STRICT 128 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 

__attribute__((used)) static int mlxsw_sp_port_ets_validate(struct mlxsw_sp_port *mlxsw_sp_port,
				      struct ieee_ets *ets)
{
	struct net_device *dev = mlxsw_sp_port->dev;
	bool has_ets_tc = false;
	int i, tx_bw_sum = 0;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_STRICT:
			break;
		case IEEE_8021QAZ_TSA_ETS:
			has_ets_tc = true;
			tx_bw_sum += ets->tc_tx_bw[i];
			break;
		default:
			netdev_err(dev, "Only strict priority and ETS are supported\n");
			return -EINVAL;
		}

		if (ets->prio_tc[i] >= IEEE_8021QAZ_MAX_TCS) {
			netdev_err(dev, "Invalid TC\n");
			return -EINVAL;
		}
	}

	if (has_ets_tc && tx_bw_sum != 100) {
		netdev_err(dev, "Total ETS bandwidth should equal 100\n");
		return -EINVAL;
	}

	return 0;
}