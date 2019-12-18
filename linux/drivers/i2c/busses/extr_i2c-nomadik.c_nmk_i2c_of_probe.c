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
struct nmk_i2c_dev {int clk_freq; int tft; int rft; int timeout; int /*<<< orphan*/  sm; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_FREQ_MODE_FAST ; 
 int /*<<< orphan*/  I2C_FREQ_MODE_STANDARD ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static void nmk_i2c_of_probe(struct device_node *np,
			     struct nmk_i2c_dev *nmk)
{
	/* Default to 100 kHz if no frequency is given in the node */
	if (of_property_read_u32(np, "clock-frequency", &nmk->clk_freq))
		nmk->clk_freq = 100000;

	/* This driver only supports 'standard' and 'fast' modes of operation. */
	if (nmk->clk_freq <= 100000)
		nmk->sm = I2C_FREQ_MODE_STANDARD;
	else
		nmk->sm = I2C_FREQ_MODE_FAST;
	nmk->tft = 1; /* Tx FIFO threshold */
	nmk->rft = 8; /* Rx FIFO threshold */
	nmk->timeout = 200; /* Slave response timeout(ms) */
}