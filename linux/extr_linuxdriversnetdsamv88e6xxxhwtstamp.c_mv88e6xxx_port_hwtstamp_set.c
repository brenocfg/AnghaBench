#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mv88e6xxx_port_hwtstamp {int /*<<< orphan*/  tstamp_config; } ;
struct mv88e6xxx_chip {TYPE_1__* info; struct mv88e6xxx_port_hwtstamp* port_hwtstamp; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int dummy; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_2__ {int /*<<< orphan*/  ptp_support; } ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hwtstamp_config*,int) ; 
 int mv88e6xxx_set_hwtstamp_config (struct mv88e6xxx_chip*,int,struct hwtstamp_config*) ; 

int mv88e6xxx_port_hwtstamp_set(struct dsa_switch *ds, int port,
				struct ifreq *ifr)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	struct mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	struct hwtstamp_config config;
	int err;

	if (!chip->info->ptp_support)
		return -EOPNOTSUPP;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	err = mv88e6xxx_set_hwtstamp_config(chip, port, &config);
	if (err)
		return err;

	/* Save the chosen configuration to be returned later. */
	memcpy(&ps->tstamp_config, &config, sizeof(config));

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}