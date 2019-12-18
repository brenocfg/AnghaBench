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
struct platform_device {int dummy; } ;
struct dsi_data {int /*<<< orphan*/  isr_tables_copy; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  isr_tables; int /*<<< orphan*/  te_timer; int /*<<< orphan*/  is_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_COMPLEXIO_IRQ_STATUS ; 
 int /*<<< orphan*/  DSI_IRQSTATUS ; 
 int DSI_IRQ_CHANNEL_MASK ; 
 int DSI_IRQ_COMPLEXIO_ERR ; 
 int DSI_IRQ_TE_TRIGGER ; 
 int /*<<< orphan*/  DSI_VC_IRQSTATUS (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_collect_irq_stats (struct platform_device*,int,int*,int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_handle_irq_errors (struct platform_device*,int,int*,int) ; 
 int /*<<< orphan*/  dsi_handle_isrs (int /*<<< orphan*/ *,int,int*,int) ; 
 int dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t omap_dsi_irq_handler(int irq, void *arg)
{
	struct platform_device *dsidev;
	struct dsi_data *dsi;
	u32 irqstatus, vcstatus[4], ciostatus;
	int i;

	dsidev = (struct platform_device *) arg;
	dsi = dsi_get_dsidrv_data(dsidev);

	if (!dsi->is_enabled)
		return IRQ_NONE;

	spin_lock(&dsi->irq_lock);

	irqstatus = dsi_read_reg(dsidev, DSI_IRQSTATUS);

	/* IRQ is not for us */
	if (!irqstatus) {
		spin_unlock(&dsi->irq_lock);
		return IRQ_NONE;
	}

	dsi_write_reg(dsidev, DSI_IRQSTATUS, irqstatus & ~DSI_IRQ_CHANNEL_MASK);
	/* flush posted write */
	dsi_read_reg(dsidev, DSI_IRQSTATUS);

	for (i = 0; i < 4; ++i) {
		if ((irqstatus & (1 << i)) == 0) {
			vcstatus[i] = 0;
			continue;
		}

		vcstatus[i] = dsi_read_reg(dsidev, DSI_VC_IRQSTATUS(i));

		dsi_write_reg(dsidev, DSI_VC_IRQSTATUS(i), vcstatus[i]);
		/* flush posted write */
		dsi_read_reg(dsidev, DSI_VC_IRQSTATUS(i));
	}

	if (irqstatus & DSI_IRQ_COMPLEXIO_ERR) {
		ciostatus = dsi_read_reg(dsidev, DSI_COMPLEXIO_IRQ_STATUS);

		dsi_write_reg(dsidev, DSI_COMPLEXIO_IRQ_STATUS, ciostatus);
		/* flush posted write */
		dsi_read_reg(dsidev, DSI_COMPLEXIO_IRQ_STATUS);
	} else {
		ciostatus = 0;
	}

#ifdef DSI_CATCH_MISSING_TE
	if (irqstatus & DSI_IRQ_TE_TRIGGER)
		del_timer(&dsi->te_timer);
#endif

	/* make a copy and unlock, so that isrs can unregister
	 * themselves */
	memcpy(&dsi->isr_tables_copy, &dsi->isr_tables,
		sizeof(dsi->isr_tables));

	spin_unlock(&dsi->irq_lock);

	dsi_handle_isrs(&dsi->isr_tables_copy, irqstatus, vcstatus, ciostatus);

	dsi_handle_irq_errors(dsidev, irqstatus, vcstatus, ciostatus);

	dsi_collect_irq_stats(dsidev, irqstatus, vcstatus, ciostatus);

	return IRQ_HANDLED;
}