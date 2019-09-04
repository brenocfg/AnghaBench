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

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int I40E_FLAG_PTP ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 

int i40e_ptp_get_ts_config(struct i40e_pf *pf, struct ifreq *ifr)
{
	struct hwtstamp_config *config = &pf->tstamp_config;

	if (!(pf->flags & I40E_FLAG_PTP))
		return -EOPNOTSUPP;

	return copy_to_user(ifr->ifr_data, config, sizeof(*config)) ?
		-EFAULT : 0;
}