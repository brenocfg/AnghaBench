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
typedef  int u16 ;
struct phy_device {int /*<<< orphan*/  attached_dev; struct dp83640_private* priv; } ;
struct dp83640_private {struct dp83640_clock* clock; } ;
struct dp83640_clock {int /*<<< orphan*/  extreg_lock; } ;

/* Variables and functions */
 int ENDIAN_FLAG ; 
 int /*<<< orphan*/  PAGE5 ; 
 int /*<<< orphan*/  PAGE6 ; 
 int /*<<< orphan*/  PSF_CFG0 ; 
 int /*<<< orphan*/  PSF_CFG1 ; 
 int PSF_EVNT_EN ; 
 int PSF_PTPVER ; 
 int PSF_RXTS_EN ; 
 int PSF_TXTS_EN ; 
 int VERSIONPTP_MASK ; 
 int VERSIONPTP_SHIFT ; 
 scalar_t__ dev_mc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_mc_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_write (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phydev_warn (struct phy_device*,char*) ; 
 int /*<<< orphan*/  status_frame_dst ; 

__attribute__((used)) static void enable_status_frames(struct phy_device *phydev, bool on)
{
	struct dp83640_private *dp83640 = phydev->priv;
	struct dp83640_clock *clock = dp83640->clock;
	u16 cfg0 = 0, ver;

	if (on)
		cfg0 = PSF_EVNT_EN | PSF_RXTS_EN | PSF_TXTS_EN | ENDIAN_FLAG;

	ver = (PSF_PTPVER & VERSIONPTP_MASK) << VERSIONPTP_SHIFT;

	mutex_lock(&clock->extreg_lock);

	ext_write(0, phydev, PAGE5, PSF_CFG0, cfg0);
	ext_write(0, phydev, PAGE6, PSF_CFG1, ver);

	mutex_unlock(&clock->extreg_lock);

	if (!phydev->attached_dev) {
		phydev_warn(phydev,
			    "expected to find an attached netdevice\n");
		return;
	}

	if (on) {
		if (dev_mc_add(phydev->attached_dev, status_frame_dst))
			phydev_warn(phydev, "failed to add mc address\n");
	} else {
		if (dev_mc_del(phydev->attached_dev, status_frame_dst))
			phydev_warn(phydev, "failed to delete mc address\n");
	}
}