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
struct fmdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_DEFAULT_RSSI_THRESHOLD ; 
 int /*<<< orphan*/  FM_DEFAULT_RX_VOLUME ; 
 int fm_rx_set_rssi_threshold (struct fmdev*,int /*<<< orphan*/ ) ; 
 int fm_rx_set_volume (struct fmdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_default_rx_configuration(struct fmdev *fmdev)
{
	int ret;

	ret = fm_rx_set_volume(fmdev, FM_DEFAULT_RX_VOLUME);
	if (ret < 0)
		return ret;

	return fm_rx_set_rssi_threshold(fmdev, FM_DEFAULT_RSSI_THRESHOLD);
}