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
typedef  int /*<<< orphan*/  u32 ;
struct psb_intel_i2c_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DATA ; 
 int /*<<< orphan*/  LPC_READ_REG (struct psb_intel_i2c_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_WRITE_REG (struct psb_intel_i2c_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGIO ; 
 int /*<<< orphan*/  RGLVL ; 

__attribute__((used)) static void set_data(void *data, int state_high)
{
	struct psb_intel_i2c_chan *chan = data;
	u32 val;

	if (state_high) {
		val = LPC_READ_REG(chan, RGIO);
		val |= GPIO_DATA;
		LPC_WRITE_REG(chan, RGIO, val);
	} else {
		val = LPC_READ_REG(chan, RGIO);
		val &= ~GPIO_DATA;
		LPC_WRITE_REG(chan, RGIO, val);
		val = LPC_READ_REG(chan, RGLVL);
		val &= ~GPIO_DATA;
		LPC_WRITE_REG(chan, RGLVL, val);
	}
}