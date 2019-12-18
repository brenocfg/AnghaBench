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
typedef  int u32 ;
struct vsc73xx {int chipid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_SYSTEM ; 
 int /*<<< orphan*/  VSC73XX_CHIPID ; 
#define  VSC73XX_CHIPID_ID_7385 131 
#define  VSC73XX_CHIPID_ID_7388 130 
#define  VSC73XX_CHIPID_ID_7395 129 
#define  VSC73XX_CHIPID_ID_7398 128 
 int VSC73XX_CHIPID_ID_MASK ; 
 int VSC73XX_CHIPID_ID_SHIFT ; 
 int VSC73XX_CHIPID_REV_MASK ; 
 int VSC73XX_CHIPID_REV_SHIFT ; 
 int /*<<< orphan*/  VSC73XX_ICPU_CTRL ; 
 int VSC73XX_ICPU_CTRL_BOOT_EN ; 
 int VSC73XX_ICPU_CTRL_ICPU_PI_EN ; 
 int /*<<< orphan*/  VSC73XX_ICPU_MBOX_VAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int vsc73xx_read (struct vsc73xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int vsc73xx_detect(struct vsc73xx *vsc)
{
	bool icpu_si_boot_en;
	bool icpu_pi_en;
	u32 val;
	u32 rev;
	int ret;
	u32 id;

	ret = vsc73xx_read(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_ICPU_MBOX_VAL, &val);
	if (ret) {
		dev_err(vsc->dev, "unable to read mailbox (%d)\n", ret);
		return ret;
	}

	if (val == 0xffffffff) {
		dev_info(vsc->dev, "chip seems dead.\n");
		return -EAGAIN;
	}

	ret = vsc73xx_read(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_CHIPID, &val);
	if (ret) {
		dev_err(vsc->dev, "unable to read chip id (%d)\n", ret);
		return ret;
	}

	id = (val >> VSC73XX_CHIPID_ID_SHIFT) &
		VSC73XX_CHIPID_ID_MASK;
	switch (id) {
	case VSC73XX_CHIPID_ID_7385:
	case VSC73XX_CHIPID_ID_7388:
	case VSC73XX_CHIPID_ID_7395:
	case VSC73XX_CHIPID_ID_7398:
		break;
	default:
		dev_err(vsc->dev, "unsupported chip, id=%04x\n", id);
		return -ENODEV;
	}

	vsc->chipid = id;
	rev = (val >> VSC73XX_CHIPID_REV_SHIFT) &
		VSC73XX_CHIPID_REV_MASK;
	dev_info(vsc->dev, "VSC%04X (rev: %d) switch found\n", id, rev);

	ret = vsc73xx_read(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_ICPU_CTRL, &val);
	if (ret) {
		dev_err(vsc->dev, "unable to read iCPU control\n");
		return ret;
	}

	/* The iCPU can always be used but can boot in different ways.
	 * If it is initially disabled and has no external memory,
	 * we are in control and can do whatever we like, else we
	 * are probably in trouble (we need some way to communicate
	 * with the running firmware) so we bail out for now.
	 */
	icpu_pi_en = !!(val & VSC73XX_ICPU_CTRL_ICPU_PI_EN);
	icpu_si_boot_en = !!(val & VSC73XX_ICPU_CTRL_BOOT_EN);
	if (icpu_si_boot_en && icpu_pi_en) {
		dev_err(vsc->dev,
			"iCPU enabled boots from SI, has external memory\n");
		dev_err(vsc->dev, "no idea how to deal with this\n");
		return -ENODEV;
	}
	if (icpu_si_boot_en && !icpu_pi_en) {
		dev_err(vsc->dev,
			"iCPU enabled boots from PI/SI, no external memory\n");
		return -EAGAIN;
	}
	if (!icpu_si_boot_en && icpu_pi_en) {
		dev_err(vsc->dev,
			"iCPU enabled, boots from PI external memory\n");
		dev_err(vsc->dev, "no idea how to deal with this\n");
		return -ENODEV;
	}
	/* !icpu_si_boot_en && !cpu_pi_en */
	dev_info(vsc->dev, "iCPU disabled, no external memory\n");

	return 0;
}