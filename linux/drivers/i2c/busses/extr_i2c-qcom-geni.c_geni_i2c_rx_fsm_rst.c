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
struct geni_i2c_dev {TYPE_1__ se; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 unsigned long RST_TIMEOUT ; 
 int RX_RESET_DONE ; 
 scalar_t__ SE_DMA_RX_FSM_RST ; 
 scalar_t__ SE_DMA_RX_IRQ_STAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void geni_i2c_rx_fsm_rst(struct geni_i2c_dev *gi2c)
{
	u32 val;
	unsigned long time_left = RST_TIMEOUT;

	writel_relaxed(1, gi2c->se.base + SE_DMA_RX_FSM_RST);
	do {
		time_left = wait_for_completion_timeout(&gi2c->done, time_left);
		val = readl_relaxed(gi2c->se.base + SE_DMA_RX_IRQ_STAT);
	} while (!(val & RX_RESET_DONE) && time_left);

	if (!(val & RX_RESET_DONE))
		dev_err(gi2c->se.dev, "Timeout resetting RX_FSM\n");
}