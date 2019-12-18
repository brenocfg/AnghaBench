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
struct qcom_ethqos {unsigned int speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethqos_configure (struct qcom_ethqos*) ; 
 int /*<<< orphan*/  ethqos_update_rgmii_clk (struct qcom_ethqos*,unsigned int) ; 

__attribute__((used)) static void ethqos_fix_mac_speed(void *priv, unsigned int speed)
{
	struct qcom_ethqos *ethqos = priv;

	ethqos->speed = speed;
	ethqos_update_rgmii_clk(ethqos, speed);
	ethqos_configure(ethqos);
}