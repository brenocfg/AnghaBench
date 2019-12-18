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
struct frad_local {int /*<<< orphan*/  config; scalar_t__* dlci; } ;
struct frad_conf {int dummy; } ;
struct conf_data {scalar_t__* dlci; } ;

/* Variables and functions */
 int CONFIG_DLCI_MAX ; 
 int /*<<< orphan*/  SDLA_DISABLE_COMMUNICATIONS ; 
 int /*<<< orphan*/  SDLA_ENABLE_COMMUNICATIONS ; 
 int /*<<< orphan*/  SDLA_SET_DLCI_CONFIGURATION ; 
 int /*<<< orphan*/  memcpy (struct conf_data*,int /*<<< orphan*/ *,int) ; 
 struct frad_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sdla_cmd (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct conf_data*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdla_reconfig(struct net_device *dev)
{
	struct frad_local *flp;
	struct conf_data  data;
	int               i, len;

	flp = netdev_priv(dev);

	len = 0;
	for(i=0;i<CONFIG_DLCI_MAX;i++)
		if (flp->dlci[i])
			data.dlci[len++] = flp->dlci[i];
	len *= 2;

	memcpy(&data, &flp->config, sizeof(struct frad_conf));
	len += sizeof(struct frad_conf);

	sdla_cmd(dev, SDLA_DISABLE_COMMUNICATIONS, 0, 0, NULL, 0, NULL, NULL);
	sdla_cmd(dev, SDLA_SET_DLCI_CONFIGURATION, 0, 0, &data, len, NULL, NULL);
	sdla_cmd(dev, SDLA_ENABLE_COMMUNICATIONS, 0, 0, NULL, 0, NULL, NULL);

	return 0;
}