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
struct share_obj {unsigned int len; int id; scalar_t__ share_buf; } ;
struct platform_device {int dummy; } ;
struct mtk_vpu {int* ipi_id_ack; int /*<<< orphan*/  vpu_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  ack_wq; struct share_obj* send_buf; } ;
typedef  enum ipi_id { ____Placeholder_ipi_id } ipi_id ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HOST_TO_VPU ; 
 int IPI_MAX ; 
 int /*<<< orphan*/  IPI_TIMEOUT_MS ; 
 int IPI_VPU_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mtk_vpu* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ vpu_cfg_readl (struct mtk_vpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpu_cfg_writel (struct mtk_vpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpu_clock_disable (struct mtk_vpu*) ; 
 int vpu_clock_enable (struct mtk_vpu*) ; 
 int /*<<< orphan*/  vpu_running (struct mtk_vpu*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

int vpu_ipi_send(struct platform_device *pdev,
		 enum ipi_id id, void *buf,
		 unsigned int len)
{
	struct mtk_vpu *vpu = platform_get_drvdata(pdev);
	struct share_obj *send_obj = vpu->send_buf;
	unsigned long timeout;
	int ret = 0;

	if (id <= IPI_VPU_INIT || id >= IPI_MAX ||
	    len > sizeof(send_obj->share_buf) || !buf) {
		dev_err(vpu->dev, "failed to send ipi message\n");
		return -EINVAL;
	}

	ret = vpu_clock_enable(vpu);
	if (ret) {
		dev_err(vpu->dev, "failed to enable vpu clock\n");
		return ret;
	}
	if (!vpu_running(vpu)) {
		dev_err(vpu->dev, "vpu_ipi_send: VPU is not running\n");
		ret = -EINVAL;
		goto clock_disable;
	}

	mutex_lock(&vpu->vpu_mutex);

	 /* Wait until VPU receives the last command */
	timeout = jiffies + msecs_to_jiffies(IPI_TIMEOUT_MS);
	do {
		if (time_after(jiffies, timeout)) {
			dev_err(vpu->dev, "vpu_ipi_send: IPI timeout!\n");
			ret = -EIO;
			goto mut_unlock;
		}
	} while (vpu_cfg_readl(vpu, HOST_TO_VPU));

	memcpy((void *)send_obj->share_buf, buf, len);
	send_obj->len = len;
	send_obj->id = id;

	vpu->ipi_id_ack[id] = false;
	/* send the command to VPU */
	vpu_cfg_writel(vpu, 0x1, HOST_TO_VPU);

	mutex_unlock(&vpu->vpu_mutex);

	/* wait for VPU's ACK */
	timeout = msecs_to_jiffies(IPI_TIMEOUT_MS);
	ret = wait_event_timeout(vpu->ack_wq, vpu->ipi_id_ack[id], timeout);
	vpu->ipi_id_ack[id] = false;
	if (ret == 0) {
		dev_err(vpu->dev, "vpu ipi %d ack time out !", id);
		ret = -EIO;
		goto clock_disable;
	}
	vpu_clock_disable(vpu);

	return 0;

mut_unlock:
	mutex_unlock(&vpu->vpu_mutex);
clock_disable:
	vpu_clock_disable(vpu);

	return ret;
}