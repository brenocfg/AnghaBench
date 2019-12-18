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
typedef  int u32 ;
struct etr_buf {scalar_t__ mode; struct catu_etr_buf* private; } ;
struct device {int dummy; } ;
struct catu_etr_buf {int /*<<< orphan*/  sladdr; } ;
struct catu_drvdata {int /*<<< orphan*/  base; TYPE_1__* csdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CATU_CONTROL_ENABLE ; 
 int /*<<< orphan*/  CATU_DEFAULT_INADDR ; 
 int CATU_MODE_PASS_THROUGH ; 
 int CATU_MODE_TRANSLATE ; 
 int /*<<< orphan*/  CATU_OS_AXICTRL ; 
 int EBUSY ; 
 scalar_t__ ETR_MODE_CATU ; 
 int catu_read_control (struct catu_drvdata*) ; 
 scalar_t__ catu_wait_for_ready (struct catu_drvdata*) ; 
 int /*<<< orphan*/  catu_write_axictrl (struct catu_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catu_write_control (struct catu_drvdata*,int) ; 
 int /*<<< orphan*/  catu_write_inaddr (struct catu_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catu_write_irqen (struct catu_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catu_write_mode (struct catu_drvdata*,int) ; 
 int /*<<< orphan*/  catu_write_sladdr (struct catu_drvdata*,int /*<<< orphan*/ ) ; 
 int coresight_claim_device_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static int catu_enable_hw(struct catu_drvdata *drvdata, void *data)
{
	int rc;
	u32 control, mode;
	struct etr_buf *etr_buf = data;
	struct device *dev = &drvdata->csdev->dev;

	if (catu_wait_for_ready(drvdata))
		dev_warn(dev, "Timeout while waiting for READY\n");

	control = catu_read_control(drvdata);
	if (control & BIT(CATU_CONTROL_ENABLE)) {
		dev_warn(dev, "CATU is already enabled\n");
		return -EBUSY;
	}

	rc = coresight_claim_device_unlocked(drvdata->base);
	if (rc)
		return rc;

	control |= BIT(CATU_CONTROL_ENABLE);

	if (etr_buf && etr_buf->mode == ETR_MODE_CATU) {
		struct catu_etr_buf *catu_buf = etr_buf->private;

		mode = CATU_MODE_TRANSLATE;
		catu_write_axictrl(drvdata, CATU_OS_AXICTRL);
		catu_write_sladdr(drvdata, catu_buf->sladdr);
		catu_write_inaddr(drvdata, CATU_DEFAULT_INADDR);
	} else {
		mode = CATU_MODE_PASS_THROUGH;
		catu_write_sladdr(drvdata, 0);
		catu_write_inaddr(drvdata, 0);
	}

	catu_write_irqen(drvdata, 0);
	catu_write_mode(drvdata, mode);
	catu_write_control(drvdata, control);
	dev_dbg(dev, "Enabled in %s mode\n",
		(mode == CATU_MODE_PASS_THROUGH) ?
		"Pass through" :
		"Translate");
	return 0;
}