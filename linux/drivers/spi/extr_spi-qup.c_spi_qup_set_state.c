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
struct spi_qup {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QUP_STATE ; 
 int QUP_STATE_CLEAR ; 
 int QUP_STATE_MASK ; 
 int QUP_STATE_PAUSE ; 
 int QUP_STATE_RESET ; 
 unsigned long SPI_DELAY_RETRY ; 
 int SPI_DELAY_THRESHOLD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spi_qup_is_valid_state (struct spi_qup*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int spi_qup_set_state(struct spi_qup *controller, u32 state)
{
	unsigned long loop;
	u32 cur_state;

	loop = 0;
	while (!spi_qup_is_valid_state(controller)) {

		usleep_range(SPI_DELAY_THRESHOLD, SPI_DELAY_THRESHOLD * 2);

		if (++loop > SPI_DELAY_RETRY)
			return -EIO;
	}

	if (loop)
		dev_dbg(controller->dev, "invalid state for %ld,us %d\n",
			loop, state);

	cur_state = readl_relaxed(controller->base + QUP_STATE);
	/*
	 * Per spec: for PAUSE_STATE to RESET_STATE, two writes
	 * of (b10) are required
	 */
	if (((cur_state & QUP_STATE_MASK) == QUP_STATE_PAUSE) &&
	    (state == QUP_STATE_RESET)) {
		writel_relaxed(QUP_STATE_CLEAR, controller->base + QUP_STATE);
		writel_relaxed(QUP_STATE_CLEAR, controller->base + QUP_STATE);
	} else {
		cur_state &= ~QUP_STATE_MASK;
		cur_state |= state;
		writel_relaxed(cur_state, controller->base + QUP_STATE);
	}

	loop = 0;
	while (!spi_qup_is_valid_state(controller)) {

		usleep_range(SPI_DELAY_THRESHOLD, SPI_DELAY_THRESHOLD * 2);

		if (++loop > SPI_DELAY_RETRY)
			return -EIO;
	}

	return 0;
}