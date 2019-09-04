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

/* Variables and functions */
 int /*<<< orphan*/  VPIF_CH0_CTRL ; 
 int VPIF_CH0_EN ; 
 int regr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void enable_channel0(int enable)
{
	if (enable)
		regw((regr(VPIF_CH0_CTRL) | (VPIF_CH0_EN)), VPIF_CH0_CTRL);
	else
		regw((regr(VPIF_CH0_CTRL) & (~VPIF_CH0_EN)), VPIF_CH0_CTRL);
}