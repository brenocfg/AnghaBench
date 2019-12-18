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
struct sirfsoc_rtc_drv {scalar_t__ rtc_base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static u32 sirfsoc_rtc_readl(struct sirfsoc_rtc_drv *rtcdrv, u32 offset)
{
	u32 val;

	regmap_read(rtcdrv->regmap, rtcdrv->rtc_base + offset, &val);
	return val;
}