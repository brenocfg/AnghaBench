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
typedef  int /*<<< orphan*/  u32 ;
struct imxdi_dev {int dsr; int /*<<< orphan*/  write_mutex; TYPE_1__* pdev; int /*<<< orphan*/  write_wait; scalar_t__ ioaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIER_WCIE ; 
 int DSR_WCF ; 
 int DSR_WEF ; 
 int EIO ; 
 int /*<<< orphan*/  clear_write_error (struct imxdi_dev*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  di_int_enable (struct imxdi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int di_write_wait(struct imxdi_dev *imxdi, u32 val, int reg)
{
	int ret;
	int rc = 0;

	/* serialize register writes */
	mutex_lock(&imxdi->write_mutex);

	/* enable the write-complete interrupt */
	di_int_enable(imxdi, DIER_WCIE);

	imxdi->dsr = 0;

	/* do the register write */
	writel(val, imxdi->ioaddr + reg);

	/* wait for the write to finish */
	ret = wait_event_interruptible_timeout(imxdi->write_wait,
			imxdi->dsr & (DSR_WCF | DSR_WEF), msecs_to_jiffies(1));
	if (ret < 0) {
		rc = ret;
		goto out;
	} else if (ret == 0) {
		dev_warn(&imxdi->pdev->dev,
				"Write-wait timeout "
				"val = 0x%08x reg = 0x%08x\n", val, reg);
	}

	/* check for write error */
	if (imxdi->dsr & DSR_WEF) {
		clear_write_error(imxdi);
		rc = -EIO;
	}

out:
	mutex_unlock(&imxdi->write_mutex);

	return rc;
}