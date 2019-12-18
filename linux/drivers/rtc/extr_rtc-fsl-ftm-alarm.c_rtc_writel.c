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
typedef  scalar_t__ u32 ;
struct ftm_rtc {scalar_t__ base; scalar_t__ big_endian; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void rtc_writel(struct ftm_rtc *dev, u32 reg, u32 val)
{
	if (dev->big_endian)
		iowrite32be(val, dev->base + reg);
	else
		iowrite32(val, dev->base + reg);
}