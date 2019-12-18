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
struct sdw_transport_params {int port_num; int blk_grp_ctrl; int blk_pkg_mode; int offset1; int offset2; int hstart; int hstop; int lane_ctrl; int sample_interval; } ;
struct sdw_cdns {int dummy; } ;
struct sdw_bus {int dummy; } ;
typedef  enum sdw_reg_bank { ____Placeholder_sdw_reg_bank } sdw_reg_bank ;

/* Variables and functions */
 int CDNS_DPN_B0_CONFIG (int) ; 
 int CDNS_DPN_B0_HCTRL (int) ; 
 int CDNS_DPN_B0_OFFSET_CTRL (int) ; 
 int CDNS_DPN_B0_SAMPLE_CTRL (int) ; 
 int CDNS_DPN_B1_CONFIG (int) ; 
 int CDNS_DPN_B1_HCTRL (int) ; 
 int CDNS_DPN_B1_OFFSET_CTRL (int) ; 
 int CDNS_DPN_B1_SAMPLE_CTRL (int) ; 
 int /*<<< orphan*/  CDNS_DPN_CONFIG_BGC ; 
 int /*<<< orphan*/  CDNS_DPN_CONFIG_BPM ; 
 int /*<<< orphan*/  CDNS_DPN_HCTRL_HSTART ; 
 int /*<<< orphan*/  CDNS_DPN_HCTRL_HSTOP ; 
 int /*<<< orphan*/  CDNS_DPN_HCTRL_LCTRL ; 
 int /*<<< orphan*/  CDNS_DPN_OFFSET_CTRL_1 ; 
 int /*<<< orphan*/  CDNS_DPN_OFFSET_CTRL_2 ; 
 int SDW_REG_SHIFT (int /*<<< orphan*/ ) ; 
 struct sdw_cdns* bus_to_cdns (struct sdw_bus*) ; 
 int cdns_readl (struct sdw_cdns*,int) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int,int) ; 

__attribute__((used)) static int cdns_transport_params(struct sdw_bus *bus,
				 struct sdw_transport_params *t_params,
				 enum sdw_reg_bank bank)
{
	struct sdw_cdns *cdns = bus_to_cdns(bus);
	int dpn_offsetctrl = 0, dpn_offsetctrl_off;
	int dpn_config = 0, dpn_config_off;
	int dpn_hctrl = 0, dpn_hctrl_off;
	int num = t_params->port_num;
	int dpn_samplectrl_off;

	/*
	 * Note: Only full data port is supported on the Master side for
	 * both PCM and PDM ports.
	 */

	if (bank) {
		dpn_config_off = CDNS_DPN_B1_CONFIG(num);
		dpn_samplectrl_off = CDNS_DPN_B1_SAMPLE_CTRL(num);
		dpn_hctrl_off = CDNS_DPN_B1_HCTRL(num);
		dpn_offsetctrl_off = CDNS_DPN_B1_OFFSET_CTRL(num);
	} else {
		dpn_config_off = CDNS_DPN_B0_CONFIG(num);
		dpn_samplectrl_off = CDNS_DPN_B0_SAMPLE_CTRL(num);
		dpn_hctrl_off = CDNS_DPN_B0_HCTRL(num);
		dpn_offsetctrl_off = CDNS_DPN_B0_OFFSET_CTRL(num);
	}

	dpn_config = cdns_readl(cdns, dpn_config_off);

	dpn_config |= (t_params->blk_grp_ctrl <<
				SDW_REG_SHIFT(CDNS_DPN_CONFIG_BGC));
	dpn_config |= (t_params->blk_pkg_mode <<
				SDW_REG_SHIFT(CDNS_DPN_CONFIG_BPM));
	cdns_writel(cdns, dpn_config_off, dpn_config);

	dpn_offsetctrl |= (t_params->offset1 <<
				SDW_REG_SHIFT(CDNS_DPN_OFFSET_CTRL_1));
	dpn_offsetctrl |= (t_params->offset2 <<
				SDW_REG_SHIFT(CDNS_DPN_OFFSET_CTRL_2));
	cdns_writel(cdns, dpn_offsetctrl_off,  dpn_offsetctrl);

	dpn_hctrl |= (t_params->hstart <<
				SDW_REG_SHIFT(CDNS_DPN_HCTRL_HSTART));
	dpn_hctrl |= (t_params->hstop << SDW_REG_SHIFT(CDNS_DPN_HCTRL_HSTOP));
	dpn_hctrl |= (t_params->lane_ctrl <<
				SDW_REG_SHIFT(CDNS_DPN_HCTRL_LCTRL));

	cdns_writel(cdns, dpn_hctrl_off, dpn_hctrl);
	cdns_writel(cdns, dpn_samplectrl_off, (t_params->sample_interval - 1));

	return 0;
}