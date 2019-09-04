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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  pixel32_to_be16 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline u16 get_pixel_val16(const uint8_t *pixel, int log_bpp)
{
	u16 pixel_val16;
	if (log_bpp == 1)
		pixel_val16 = *(const uint16_t *)pixel;
	else
		pixel_val16 = pixel32_to_be16(*(const uint32_t *)pixel);
	return pixel_val16;
}