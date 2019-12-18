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
struct TYPE_2__ {int /*<<< orphan*/ * rfs_chan_spec_scan; } ;
struct ath10k {TYPE_1__ spectral; } ;

/* Variables and functions */
 int /*<<< orphan*/  relay_close (int /*<<< orphan*/ *) ; 

void ath10k_spectral_destroy(struct ath10k *ar)
{
	if (ar->spectral.rfs_chan_spec_scan) {
		relay_close(ar->spectral.rfs_chan_spec_scan);
		ar->spectral.rfs_chan_spec_scan = NULL;
	}
}