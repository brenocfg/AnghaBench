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
struct xiic_i2c {int dummy; } ;

/* Variables and functions */
 int IIC_TX_FIFO_DEPTH ; 
 int /*<<< orphan*/  XIIC_TFO_REG_OFFSET ; 
 int xiic_getreg8 (struct xiic_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xiic_tx_fifo_space(struct xiic_i2c *i2c)
{
	/* return the actual space left in the FIFO */
	return IIC_TX_FIFO_DEPTH - xiic_getreg8(i2c, XIIC_TFO_REG_OFFSET) - 1;
}