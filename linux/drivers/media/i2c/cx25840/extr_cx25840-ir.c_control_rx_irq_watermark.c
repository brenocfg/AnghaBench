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
struct i2c_client {int dummy; } ;
typedef  enum rx_fifo_watermark { ____Placeholder_rx_fifo_watermark } rx_fifo_watermark ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_RIC ; 
 int /*<<< orphan*/  CX25840_IR_CNTRL_REG ; 
 int /*<<< orphan*/  cx25840_and_or4 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void control_rx_irq_watermark(struct i2c_client *c,
					    enum rx_fifo_watermark level)
{
	cx25840_and_or4(c, CX25840_IR_CNTRL_REG, ~CNTRL_RIC, level);
}