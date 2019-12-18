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
struct ftm_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_SC ; 
 int /*<<< orphan*/  FTM_SC_TOIE ; 
 int /*<<< orphan*/  rtc_readl (struct ftm_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (struct ftm_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ftm_irq_enable(struct ftm_rtc *rtc)
{
	u32 val;

	val = rtc_readl(rtc, FTM_SC);
	val |= FTM_SC_TOIE;
	rtc_writel(rtc, FTM_SC, val);
}