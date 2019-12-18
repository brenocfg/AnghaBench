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
 scalar_t__ ioread32 (scalar_t__) ; 
 scalar_t__ ioread32be (scalar_t__) ; 

__attribute__((used)) static inline u32 rtc_readl(struct ftm_rtc *dev, u32 reg)
{
	if (dev->big_endian)
		return ioread32be(dev->base + reg);
	else
		return ioread32(dev->base + reg);
}