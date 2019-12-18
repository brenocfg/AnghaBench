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
struct psb_intel_i2c_chan {int dummy; } ;

/* Variables and functions */
 int GPIO_CLOCK ; 
 int LPC_READ_REG (struct psb_intel_i2c_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_WRITE_REG (struct psb_intel_i2c_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RGIO ; 
 int /*<<< orphan*/  RGLVL ; 

__attribute__((used)) static int get_clock(void *data)
{
	struct psb_intel_i2c_chan *chan = data;
	u32 val, tmp;

	val = LPC_READ_REG(chan, RGIO);
	val |= GPIO_CLOCK;
	LPC_WRITE_REG(chan, RGIO, val);
	tmp = LPC_READ_REG(chan, RGLVL);
	val = (LPC_READ_REG(chan, RGLVL) & GPIO_CLOCK) ? 1 : 0;

	return val;
}