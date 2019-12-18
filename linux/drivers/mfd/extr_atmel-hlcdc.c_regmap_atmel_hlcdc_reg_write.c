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
struct atmel_hlcdc_regmap {scalar_t__ regs; } ;

/* Variables and functions */
 unsigned int ATMEL_HLCDC_DIS ; 
 int ATMEL_HLCDC_SIP ; 
 scalar_t__ ATMEL_HLCDC_SR ; 
 int /*<<< orphan*/  readl_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int regmap_atmel_hlcdc_reg_write(void *context, unsigned int reg,
					unsigned int val)
{
	struct atmel_hlcdc_regmap *hregmap = context;

	if (reg <= ATMEL_HLCDC_DIS) {
		u32 status;

		readl_poll_timeout_atomic(hregmap->regs + ATMEL_HLCDC_SR,
					  status, !(status & ATMEL_HLCDC_SIP),
					  1, 100);
	}

	writel(val, hregmap->regs + reg);

	return 0;
}