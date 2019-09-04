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
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int dummy; } ;
struct i40e_pf {int flags; struct hwtstamp_config tstamp_config; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int I40E_FLAG_PTP ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int i40e_ptp_set_timestamp_mode (struct i40e_pf*,struct hwtstamp_config*) ; 

int i40e_ptp_set_ts_config(struct i40e_pf *pf, struct ifreq *ifr)
{
	struct hwtstamp_config config;
	int err;

	if (!(pf->flags & I40E_FLAG_PTP))
		return -EOPNOTSUPP;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	err = i40e_ptp_set_timestamp_mode(pf, &config);
	if (err)
		return err;

	/* save these settings for future reference */
	pf->tstamp_config = config;

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}