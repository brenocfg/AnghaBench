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
struct lantiq_ssc_spi {scalar_t__ regbase; } ;

/* Variables and functions */
 scalar_t__ __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void lantiq_ssc_maskl(const struct lantiq_ssc_spi *spi, u32 clr,
			     u32 set, u32 reg)
{
	u32 val = __raw_readl(spi->regbase + reg);

	val &= ~clr;
	val |= set;
	__raw_writel(val, spi->regbase + reg);
}