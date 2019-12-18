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
typedef  int u8 ;
struct fmdev {int curr_fmmode; } ;

/* Variables and functions */
 int EINVAL ; 
 int FM_MODE_ENTRY_MAX ; 
#define  FM_MODE_OFF 130 
#define  FM_MODE_RX 129 
#define  FM_MODE_TX 128 
 int fm_power_down (struct fmdev*) ; 
 int fm_power_up (struct fmdev*,int) ; 
 int /*<<< orphan*/  fmdbg (char*,...) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 int load_default_rx_configuration (struct fmdev*) ; 
 int /*<<< orphan*/  msleep (int) ; 

int fmc_set_mode(struct fmdev *fmdev, u8 fm_mode)
{
	int ret = 0;

	if (fm_mode >= FM_MODE_ENTRY_MAX) {
		fmerr("Invalid FM mode\n");
		return -EINVAL;
	}
	if (fmdev->curr_fmmode == fm_mode) {
		fmdbg("Already fm is in mode(%d)\n", fm_mode);
		return ret;
	}

	switch (fm_mode) {
	case FM_MODE_OFF:	/* OFF Mode */
		ret = fm_power_down(fmdev);
		if (ret < 0) {
			fmerr("Failed to set OFF mode\n");
			return ret;
		}
		break;

	case FM_MODE_TX:	/* TX Mode */
	case FM_MODE_RX:	/* RX Mode */
		/* Power down before switching to TX or RX mode */
		if (fmdev->curr_fmmode != FM_MODE_OFF) {
			ret = fm_power_down(fmdev);
			if (ret < 0) {
				fmerr("Failed to set OFF mode\n");
				return ret;
			}
			msleep(30);
		}
		ret = fm_power_up(fmdev, fm_mode);
		if (ret < 0) {
			fmerr("Failed to load firmware\n");
			return ret;
		}
	}
	fmdev->curr_fmmode = fm_mode;

	/* Set default configuration */
	if (fmdev->curr_fmmode == FM_MODE_RX) {
		fmdbg("Loading default rx configuration..\n");
		ret = load_default_rx_configuration(fmdev);
		if (ret < 0)
			fmerr("Failed to load default values\n");
	}

	return ret;
}