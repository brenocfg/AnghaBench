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
struct dentry {int dummy; } ;
struct ath_spec_scan_priv {int /*<<< orphan*/  rfs_chan_spec_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct ath_spec_scan_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_spec_scan_ctl ; 
 int /*<<< orphan*/  fops_spectral_count ; 
 int /*<<< orphan*/  fops_spectral_fft_period ; 
 int /*<<< orphan*/  fops_spectral_period ; 
 int /*<<< orphan*/  fops_spectral_short_repeat ; 
 int /*<<< orphan*/  relay_open (char*,struct dentry*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfs_spec_scan_cb ; 

void ath9k_cmn_spectral_init_debug(struct ath_spec_scan_priv *spec_priv,
				   struct dentry *debugfs_phy)
{
	spec_priv->rfs_chan_spec_scan = relay_open("spectral_scan",
					    debugfs_phy,
					    1024, 256, &rfs_spec_scan_cb,
					    NULL);
	if (!spec_priv->rfs_chan_spec_scan)
		return;

	debugfs_create_file("spectral_scan_ctl",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spec_scan_ctl);
	debugfs_create_file("spectral_short_repeat",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_short_repeat);
	debugfs_create_file("spectral_count",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_count);
	debugfs_create_file("spectral_period",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_period);
	debugfs_create_file("spectral_fft_period",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_fft_period);
}