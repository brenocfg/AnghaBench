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
struct ath_spec_scan_priv {int /*<<< orphan*/ * rfs_chan_spec_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  relay_close (int /*<<< orphan*/ *) ; 

void ath9k_cmn_spectral_deinit_debug(struct ath_spec_scan_priv *spec_priv)
{
	if (spec_priv->rfs_chan_spec_scan) {
		relay_close(spec_priv->rfs_chan_spec_scan);
		spec_priv->rfs_chan_spec_scan = NULL;
	}
}