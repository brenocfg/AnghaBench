#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int* data; unsigned char height; } ;

/* Variables and functions */
 TYPE_1__* font ; 

__attribute__((used)) static void early_efi_write_char(u32 *dst, unsigned char c, unsigned int h)
{
	const u32 color_black = 0x00000000;
	const u32 color_white = 0x00ffffff;
	const u8 *src;
	u8 s8;
	int m;

	src = font->data + c * font->height;
	s8 = *(src + h);

	for (m = 0; m < 8; m++) {
		if ((s8 >> (7 - m)) & 1)
			*dst = color_white;
		else
			*dst = color_black;
		dst++;
	}
}