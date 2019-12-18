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
struct imx7_csi {int last_eof; int /*<<< orphan*/  underrun_buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  sd; int /*<<< orphan*/  last_eof_completion; int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_MEDIA_EOF_TIMEOUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  imx7_csi_dma_unsetup_vb2_buf (struct imx7_csi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_hw_disable_irq (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx_media_free_dma_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void imx7_csi_dma_stop(struct imx7_csi *csi)
{
	unsigned long timeout_jiffies;
	unsigned long flags;
	int ret;

	/* mark next EOF interrupt as the last before stream off */
	spin_lock_irqsave(&csi->irqlock, flags);
	csi->last_eof = true;
	spin_unlock_irqrestore(&csi->irqlock, flags);

	/*
	 * and then wait for interrupt handler to mark completion.
	 */
	timeout_jiffies = msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT);
	ret = wait_for_completion_timeout(&csi->last_eof_completion,
					  timeout_jiffies);
	if (ret == 0)
		v4l2_warn(&csi->sd, "wait last EOF timeout\n");

	imx7_csi_hw_disable_irq(csi);

	imx7_csi_dma_unsetup_vb2_buf(csi, VB2_BUF_STATE_ERROR);

	imx_media_free_dma_buf(csi->dev, &csi->underrun_buf);
}