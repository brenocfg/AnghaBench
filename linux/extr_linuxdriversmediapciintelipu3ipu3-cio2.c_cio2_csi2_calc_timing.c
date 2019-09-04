#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_querymenu {scalar_t__ value; int /*<<< orphan*/  index; int /*<<< orphan*/  id; } ;
struct v4l2_ctrl {int dummy; } ;
struct device {int dummy; } ;
struct cio2_queue {TYPE_2__* sensor; } ;
struct cio2_device {TYPE_1__* pci_dev; } ;
struct cio2_csi2_timing {void* dat_settle; void* dat_termen; void* clk_settle; void* clk_termen; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_SETTLE_CLANE_A ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_SETTLE_CLANE_B ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_SETTLE_DEFAULT ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_SETTLE_DLANE_A ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_SETTLE_DLANE_B ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_TERMEN_CLANE_A ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_TERMEN_CLANE_B ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_TERMEN_DEFAULT ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_TERMEN_DLANE_A ; 
 int /*<<< orphan*/  CIO2_CSIRX_DLY_CNT_TERMEN_DLANE_B ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPIPE ; 
 int /*<<< orphan*/  V4L2_CID_LINK_FREQ ; 
 void* cio2_rx_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (struct v4l2_ctrl*) ; 
 int v4l2_querymenu (int /*<<< orphan*/ ,struct v4l2_querymenu*) ; 

__attribute__((used)) static int cio2_csi2_calc_timing(struct cio2_device *cio2, struct cio2_queue *q,
				 struct cio2_csi2_timing *timing)
{
	struct device *dev = &cio2->pci_dev->dev;
	struct v4l2_querymenu qm = {.id = V4L2_CID_LINK_FREQ, };
	struct v4l2_ctrl *link_freq;
	s64 freq;
	int r;

	if (!q->sensor)
		return -ENODEV;

	link_freq = v4l2_ctrl_find(q->sensor->ctrl_handler, V4L2_CID_LINK_FREQ);
	if (!link_freq) {
		dev_err(dev, "failed to find LINK_FREQ\n");
		return -EPIPE;
	}

	qm.index = v4l2_ctrl_g_ctrl(link_freq);
	r = v4l2_querymenu(q->sensor->ctrl_handler, &qm);
	if (r) {
		dev_err(dev, "failed to get menu item\n");
		return r;
	}

	if (!qm.value) {
		dev_err(dev, "error invalid link_freq\n");
		return -EINVAL;
	}
	freq = qm.value;

	timing->clk_termen = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_TERMEN_CLANE_A,
					    CIO2_CSIRX_DLY_CNT_TERMEN_CLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_TERMEN_DEFAULT);
	timing->clk_settle = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_SETTLE_CLANE_A,
					    CIO2_CSIRX_DLY_CNT_SETTLE_CLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_SETTLE_DEFAULT);
	timing->dat_termen = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_TERMEN_DLANE_A,
					    CIO2_CSIRX_DLY_CNT_TERMEN_DLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_TERMEN_DEFAULT);
	timing->dat_settle = cio2_rx_timing(CIO2_CSIRX_DLY_CNT_SETTLE_DLANE_A,
					    CIO2_CSIRX_DLY_CNT_SETTLE_DLANE_B,
					    freq,
					    CIO2_CSIRX_DLY_CNT_SETTLE_DEFAULT);

	dev_dbg(dev, "freq ct value is %d\n", timing->clk_termen);
	dev_dbg(dev, "freq cs value is %d\n", timing->clk_settle);
	dev_dbg(dev, "freq dt value is %d\n", timing->dat_termen);
	dev_dbg(dev, "freq ds value is %d\n", timing->dat_settle);

	return 0;
}