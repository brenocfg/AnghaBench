#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct omap_ssi_port {int /*<<< orphan*/  pdev; } ;
struct omap_ssi_controller {scalar_t__ sys; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct hsi_port {int /*<<< orphan*/  num; TYPE_1__ device; } ;
struct hsi_msg {scalar_t__ ttype; int /*<<< orphan*/  status; scalar_t__ actual_len; int /*<<< orphan*/  channel; int /*<<< orphan*/  cl; } ;
struct hsi_controller {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 scalar_t__ HSI_MSG_WRITE ; 
 int /*<<< orphan*/  HSI_STATUS_PROCEEDING ; 
 int SSI_DATAACCEPT (int /*<<< orphan*/ ) ; 
 int SSI_DATAAVAILABLE (int /*<<< orphan*/ ) ; 
 int SSI_ERROROCCURED ; 
 scalar_t__ SSI_MPU_ENABLE_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 struct hsi_port* hsi_get_port (int /*<<< orphan*/ ) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct hsi_controller* to_hsi_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ssi_start_pio(struct hsi_msg *msg)
{
	struct hsi_port *port = hsi_get_port(msg->cl);
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	struct hsi_controller *ssi = to_hsi_controller(port->device.parent);
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	u32 val;

	pm_runtime_get(omap_port->pdev);

	if (!pm_runtime_active(omap_port->pdev)) {
		dev_warn(&port->device, "ssi_start_pio called without runtime PM!\n");
		pm_runtime_put_autosuspend(omap_port->pdev);
		return -EREMOTEIO;
	}

	if (msg->ttype == HSI_MSG_WRITE) {
		val = SSI_DATAACCEPT(msg->channel);
		/* Hold clocks for pio writes */
		pm_runtime_get(omap_port->pdev);
	} else {
		val = SSI_DATAAVAILABLE(msg->channel) | SSI_ERROROCCURED;
	}
	dev_dbg(&port->device, "Single %s transfer\n",
						msg->ttype ? "write" : "read");
	val |= readl(omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	writel(val, omap_ssi->sys + SSI_MPU_ENABLE_REG(port->num, 0));
	pm_runtime_put_autosuspend(omap_port->pdev);
	msg->actual_len = 0;
	msg->status = HSI_STATUS_PROCEEDING;

	return 0;
}