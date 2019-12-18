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
struct mwifiex_tdls_config_cs_params {int /*<<< orphan*/  thr_directlink; int /*<<< orphan*/  thr_otherlink; int /*<<< orphan*/  unit_time; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_TDLS_CS_PARAMS ; 
 int /*<<< orphan*/  HostCmd_CMD_TDLS_CONFIG ; 
 int /*<<< orphan*/  MWIFIEX_DEF_CS_THR_OTHERLINK ; 
 int /*<<< orphan*/  MWIFIEX_DEF_CS_UNIT_TIME ; 
 int /*<<< orphan*/  MWIFIEX_DEF_THR_DIRECTLINK ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_tdls_config_cs_params*,int) ; 

int mwifiex_config_tdls_cs_params(struct mwifiex_private *priv)
{
	struct mwifiex_tdls_config_cs_params config_tdls_cs_params;

	config_tdls_cs_params.unit_time = MWIFIEX_DEF_CS_UNIT_TIME;
	config_tdls_cs_params.thr_otherlink = MWIFIEX_DEF_CS_THR_OTHERLINK;
	config_tdls_cs_params.thr_directlink = MWIFIEX_DEF_THR_DIRECTLINK;

	return mwifiex_send_cmd(priv, HostCmd_CMD_TDLS_CONFIG,
				ACT_TDLS_CS_PARAMS, 0,
				&config_tdls_cs_params, true);
}