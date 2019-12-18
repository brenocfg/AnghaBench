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
struct qcom_ethqos {int /*<<< orphan*/  rgmii_clk_rate; int /*<<< orphan*/  rgmii_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGMII_1000_NOM_CLK_FREQ ; 
 int /*<<< orphan*/  RGMII_ID_MODE_100_LOW_SVS_CLK_FREQ ; 
 int /*<<< orphan*/  RGMII_ID_MODE_10_LOW_SVS_CLK_FREQ ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ethqos_update_rgmii_clk(struct qcom_ethqos *ethqos, unsigned int speed)
{
	switch (speed) {
	case SPEED_1000:
		ethqos->rgmii_clk_rate =  RGMII_1000_NOM_CLK_FREQ;
		break;

	case SPEED_100:
		ethqos->rgmii_clk_rate =  RGMII_ID_MODE_100_LOW_SVS_CLK_FREQ;
		break;

	case SPEED_10:
		ethqos->rgmii_clk_rate =  RGMII_ID_MODE_10_LOW_SVS_CLK_FREQ;
		break;
	}

	clk_set_rate(ethqos->rgmii_clk, ethqos->rgmii_clk_rate);
}