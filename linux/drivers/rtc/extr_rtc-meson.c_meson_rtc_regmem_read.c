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
struct meson_rtc {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 unsigned int RTC_REGMEM_0 ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int meson_rtc_regmem_read(void *context, unsigned int offset,
				 void *buf, size_t bytes)
{
	struct meson_rtc *rtc = context;
	unsigned int read_offset, read_size;

	read_offset = RTC_REGMEM_0 + (offset / 4);
	read_size = bytes / 4;

	return regmap_bulk_read(rtc->serial, read_offset, buf, read_size);
}