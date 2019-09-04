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
struct msm_dsi_host {int /*<<< orphan*/  sfpb; } ;
typedef  enum sfpb_ahb_arb_master_port_en { ____Placeholder_sfpb_ahb_arb_master_port_en } sfpb_ahb_arb_master_port_en ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SFPB_GPREG ; 
 int /*<<< orphan*/  SFPB_GPREG_MASTER_PORT_EN (int) ; 
 int /*<<< orphan*/  SFPB_GPREG_MASTER_PORT_EN__MASK ; 
 int SFPB_MASTER_PORT_DISABLE ; 
 int SFPB_MASTER_PORT_ENABLE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_dsi_sfpb_config(struct msm_dsi_host *msm_host, bool enable)
{
	enum sfpb_ahb_arb_master_port_en en;

	if (!msm_host->sfpb)
		return;

	en = enable ? SFPB_MASTER_PORT_ENABLE : SFPB_MASTER_PORT_DISABLE;

	regmap_update_bits(msm_host->sfpb, REG_SFPB_GPREG,
			SFPB_GPREG_MASTER_PORT_EN__MASK,
			SFPB_GPREG_MASTER_PORT_EN(en));
}