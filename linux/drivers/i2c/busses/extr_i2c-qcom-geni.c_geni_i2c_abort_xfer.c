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
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ base; } ;
struct geni_i2c_dev {TYPE_1__ se; int /*<<< orphan*/  done; int /*<<< orphan*/  lock; int /*<<< orphan*/ * cur; } ;

/* Variables and functions */
 unsigned long ABORT_TIMEOUT ; 
 int /*<<< orphan*/  GENI_TIMEOUT ; 
 int M_CMD_ABORT_EN ; 
 scalar_t__ SE_GENI_M_IRQ_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  geni_i2c_err (struct geni_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geni_se_abort_m_cmd (TYPE_1__*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void geni_i2c_abort_xfer(struct geni_i2c_dev *gi2c)
{
	u32 val;
	unsigned long time_left = ABORT_TIMEOUT;
	unsigned long flags;

	spin_lock_irqsave(&gi2c->lock, flags);
	geni_i2c_err(gi2c, GENI_TIMEOUT);
	gi2c->cur = NULL;
	geni_se_abort_m_cmd(&gi2c->se);
	spin_unlock_irqrestore(&gi2c->lock, flags);
	do {
		time_left = wait_for_completion_timeout(&gi2c->done, time_left);
		val = readl_relaxed(gi2c->se.base + SE_GENI_M_IRQ_STATUS);
	} while (!(val & M_CMD_ABORT_EN) && time_left);

	if (!(val & M_CMD_ABORT_EN))
		dev_err(gi2c->se.dev, "Timeout abort_m_cmd\n");
}