#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  a1; int /*<<< orphan*/  intb; int /*<<< orphan*/  lrout; int /*<<< orphan*/  icop; int /*<<< orphan*/  icon; int /*<<< orphan*/  icip; int /*<<< orphan*/  icin; int /*<<< orphan*/  qout; int /*<<< orphan*/  iout; int /*<<< orphan*/  iqfs; int /*<<< orphan*/  iqclk; int /*<<< orphan*/  xout; int /*<<< orphan*/  dout; int /*<<< orphan*/  dfs; int /*<<< orphan*/  dclk; } ;
struct si476x_core {TYPE_2__* client; TYPE_1__ pinmux; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int si476x_core_cmd_ana_audio_pin_cfg (struct si476x_core*,int /*<<< orphan*/ ) ; 
 int si476x_core_cmd_dig_audio_pin_cfg (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si476x_core_cmd_ic_link_gpo_ctl_pin_cfg (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si476x_core_cmd_intb_pin_cfg (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si476x_core_cmd_zif_pin_cfg (struct si476x_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si476x_core_config_pinmux(struct si476x_core *core)
{
	int err;
	dev_dbg(&core->client->dev, "Configuring pinmux\n");
	err = si476x_core_cmd_dig_audio_pin_cfg(core,
						core->pinmux.dclk,
						core->pinmux.dfs,
						core->pinmux.dout,
						core->pinmux.xout);
	if (err < 0) {
		dev_err(&core->client->dev,
			"Failed to configure digital audio pins(err = %d)\n",
			err);
		return err;
	}

	err = si476x_core_cmd_zif_pin_cfg(core,
					  core->pinmux.iqclk,
					  core->pinmux.iqfs,
					  core->pinmux.iout,
					  core->pinmux.qout);
	if (err < 0) {
		dev_err(&core->client->dev,
			"Failed to configure ZIF pins(err = %d)\n",
			err);
		return err;
	}

	err = si476x_core_cmd_ic_link_gpo_ctl_pin_cfg(core,
						      core->pinmux.icin,
						      core->pinmux.icip,
						      core->pinmux.icon,
						      core->pinmux.icop);
	if (err < 0) {
		dev_err(&core->client->dev,
			"Failed to configure IC-Link/GPO pins(err = %d)\n",
			err);
		return err;
	}

	err = si476x_core_cmd_ana_audio_pin_cfg(core,
						core->pinmux.lrout);
	if (err < 0) {
		dev_err(&core->client->dev,
			"Failed to configure analog audio pins(err = %d)\n",
			err);
		return err;
	}

	err = si476x_core_cmd_intb_pin_cfg(core,
					   core->pinmux.intb,
					   core->pinmux.a1);
	if (err < 0) {
		dev_err(&core->client->dev,
			"Failed to configure interrupt pins(err = %d)\n",
			err);
		return err;
	}

	return 0;
}