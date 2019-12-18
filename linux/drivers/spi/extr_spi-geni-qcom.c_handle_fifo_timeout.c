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
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;
struct geni_se {scalar_t__ base; } ;
struct spi_geni_master {int /*<<< orphan*/  dev; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  cur_mcmd; struct geni_se se; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CANCEL ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  geni_se_abort_m_cmd (struct geni_se*) ; 
 int /*<<< orphan*/  geni_se_cancel_m_cmd (struct geni_se*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct spi_geni_master* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void handle_fifo_timeout(struct spi_master *spi,
				struct spi_message *msg)
{
	struct spi_geni_master *mas = spi_master_get_devdata(spi);
	unsigned long time_left, flags;
	struct geni_se *se = &mas->se;

	spin_lock_irqsave(&mas->lock, flags);
	reinit_completion(&mas->xfer_done);
	mas->cur_mcmd = CMD_CANCEL;
	geni_se_cancel_m_cmd(se);
	writel(0, se->base + SE_GENI_TX_WATERMARK_REG);
	spin_unlock_irqrestore(&mas->lock, flags);
	time_left = wait_for_completion_timeout(&mas->xfer_done, HZ);
	if (time_left)
		return;

	spin_lock_irqsave(&mas->lock, flags);
	reinit_completion(&mas->xfer_done);
	geni_se_abort_m_cmd(se);
	spin_unlock_irqrestore(&mas->lock, flags);
	time_left = wait_for_completion_timeout(&mas->xfer_done, HZ);
	if (!time_left)
		dev_err(mas->dev, "Failed to cancel/abort m_cmd\n");
}