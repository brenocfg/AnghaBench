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
struct vpu_run {int signaled; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  wq; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mtk_vpu {int fw_loaded; int /*<<< orphan*/  vpu_mutex; int /*<<< orphan*/  dev; struct vpu_run run; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FW ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  INIT_TIMEOUT_MS ; 
 int /*<<< orphan*/  P_FW ; 
 int /*<<< orphan*/  VPU_D_FW ; 
 int /*<<< orphan*/  VPU_P_FW ; 
 int /*<<< orphan*/  VPU_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int load_requested_vpu (struct mtk_vpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mtk_vpu* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  vpu_cfg_writel (struct mtk_vpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpu_clock_disable (struct mtk_vpu*) ; 
 int vpu_clock_enable (struct mtk_vpu*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int vpu_load_firmware(struct platform_device *pdev)
{
	struct mtk_vpu *vpu;
	struct device *dev = &pdev->dev;
	struct vpu_run *run;
	int ret;

	if (!pdev) {
		dev_err(dev, "VPU platform device is invalid\n");
		return -EINVAL;
	}

	vpu = platform_get_drvdata(pdev);
	run = &vpu->run;

	mutex_lock(&vpu->vpu_mutex);
	if (vpu->fw_loaded) {
		mutex_unlock(&vpu->vpu_mutex);
		return 0;
	}
	mutex_unlock(&vpu->vpu_mutex);

	ret = vpu_clock_enable(vpu);
	if (ret) {
		dev_err(dev, "enable clock failed %d\n", ret);
		return ret;
	}

	mutex_lock(&vpu->vpu_mutex);

	run->signaled = false;
	dev_dbg(vpu->dev, "firmware request\n");
	/* Downloading program firmware to device*/
	ret = load_requested_vpu(vpu, P_FW);
	if (ret < 0) {
		dev_err(dev, "Failed to request %s, %d\n", VPU_P_FW, ret);
		goto OUT_LOAD_FW;
	}

	/* Downloading data firmware to device */
	ret = load_requested_vpu(vpu, D_FW);
	if (ret < 0) {
		dev_err(dev, "Failed to request %s, %d\n", VPU_D_FW, ret);
		goto OUT_LOAD_FW;
	}

	vpu->fw_loaded = true;
	/* boot up vpu */
	vpu_cfg_writel(vpu, 0x1, VPU_RESET);

	ret = wait_event_interruptible_timeout(run->wq,
					       run->signaled,
					       msecs_to_jiffies(INIT_TIMEOUT_MS)
					       );
	if (ret == 0) {
		ret = -ETIME;
		dev_err(dev, "wait vpu initialization timeout!\n");
		goto OUT_LOAD_FW;
	} else if (-ERESTARTSYS == ret) {
		dev_err(dev, "wait vpu interrupted by a signal!\n");
		goto OUT_LOAD_FW;
	}

	ret = 0;
	dev_info(dev, "vpu is ready. Fw version %s\n", run->fw_ver);

OUT_LOAD_FW:
	mutex_unlock(&vpu->vpu_mutex);
	vpu_clock_disable(vpu);

	return ret;
}