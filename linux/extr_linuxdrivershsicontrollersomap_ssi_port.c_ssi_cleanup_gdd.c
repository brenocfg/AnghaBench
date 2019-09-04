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
struct omap_ssi_port {int /*<<< orphan*/  pdev; } ;
struct omap_ssi_controller {scalar_t__ sys; TYPE_1__* gdd_trn; scalar_t__ gdd; } ;
struct hsi_port {int dummy; } ;
struct hsi_msg {scalar_t__ ttype; struct hsi_client* cl; } ;
struct hsi_controller {int dummy; } ;
struct hsi_client {int dummy; } ;
struct TYPE_2__ {struct hsi_msg* msg; } ;

/* Variables and functions */
 scalar_t__ HSI_MSG_READ ; 
 scalar_t__ SSI_GDD_CCR_REG (unsigned int) ; 
 scalar_t__ SSI_GDD_MPU_IRQ_ENABLE_REG ; 
 scalar_t__ SSI_GDD_MPU_IRQ_STATUS_REG ; 
 unsigned int SSI_MAX_GDD_LCH ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 
 int /*<<< orphan*/  writew_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ssi_cleanup_gdd(struct hsi_controller *ssi, struct hsi_client *cl)
{
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	struct hsi_port *port = hsi_get_port(cl);
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	struct hsi_msg *msg;
	unsigned int i;
	u32 val = 0;
	u32 tmp;

	for (i = 0; i < SSI_MAX_GDD_LCH; i++) {
		msg = omap_ssi->gdd_trn[i].msg;
		if ((!msg) || (msg->cl != cl))
			continue;
		writew_relaxed(0, omap_ssi->gdd + SSI_GDD_CCR_REG(i));
		val |= (1 << i);
		/*
		 * Clock references for write will be handled in
		 * ssi_cleanup_queues
		 */
		if (msg->ttype == HSI_MSG_READ) {
			pm_runtime_mark_last_busy(omap_port->pdev);
			pm_runtime_put_autosuspend(omap_port->pdev);
		}
		omap_ssi->gdd_trn[i].msg = NULL;
	}
	tmp = readl_relaxed(omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	tmp &= ~val;
	writel_relaxed(tmp, omap_ssi->sys + SSI_GDD_MPU_IRQ_ENABLE_REG);
	writel(val, omap_ssi->sys + SSI_GDD_MPU_IRQ_STATUS_REG);
}