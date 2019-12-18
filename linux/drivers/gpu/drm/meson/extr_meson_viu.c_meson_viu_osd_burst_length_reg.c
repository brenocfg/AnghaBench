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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t meson_viu_osd_burst_length_reg(uint32_t length)
{
	uint32_t val = (((length & 0x80) % 24) / 12);

	return (((val & 0x3) << 10) | (((val & 0x4) >> 2) << 31));
}