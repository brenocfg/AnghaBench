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
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4740_rtc {scalar_t__ type; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ID_JZ4780 ; 
 int jz4740_rtc_wait_write_ready (struct jz4740_rtc*) ; 
 int jz4780_rtc_enable_write (struct jz4740_rtc*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int jz4740_rtc_reg_write(struct jz4740_rtc *rtc, size_t reg,
	uint32_t val)
{
	int ret = 0;

	if (rtc->type >= ID_JZ4780)
		ret = jz4780_rtc_enable_write(rtc);
	if (ret == 0)
		ret = jz4740_rtc_wait_write_ready(rtc);
	if (ret == 0)
		writel(val, rtc->base + reg);

	return ret;
}