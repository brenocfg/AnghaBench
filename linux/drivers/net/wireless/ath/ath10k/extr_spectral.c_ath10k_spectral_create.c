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
struct TYPE_4__ {int /*<<< orphan*/  debugfs_phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rfs_chan_spec_scan; } ;
struct ath10k {TYPE_2__ debug; TYPE_1__ spectral; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ath10k*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_spec_scan_ctl ; 
 int /*<<< orphan*/  fops_spectral_bins ; 
 int /*<<< orphan*/  fops_spectral_count ; 
 int /*<<< orphan*/  relay_open (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfs_spec_scan_cb ; 

int ath10k_spectral_create(struct ath10k *ar)
{
	/* The buffer size covers whole channels in dual bands up to 128 bins.
	 * Scan with bigger than 128 bins needs to be run on single band each.
	 */
	ar->spectral.rfs_chan_spec_scan = relay_open("spectral_scan",
						     ar->debug.debugfs_phy,
						     1140, 2500,
						     &rfs_spec_scan_cb, NULL);
	debugfs_create_file("spectral_scan_ctl",
			    0600,
			    ar->debug.debugfs_phy, ar,
			    &fops_spec_scan_ctl);
	debugfs_create_file("spectral_count",
			    0600,
			    ar->debug.debugfs_phy, ar,
			    &fops_spectral_count);
	debugfs_create_file("spectral_bins",
			    0600,
			    ar->debug.debugfs_phy, ar,
			    &fops_spectral_bins);

	return 0;
}