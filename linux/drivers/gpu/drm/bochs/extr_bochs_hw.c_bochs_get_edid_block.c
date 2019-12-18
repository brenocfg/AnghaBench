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
typedef  int /*<<< orphan*/  u8 ;
struct bochs_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int EDID_LENGTH ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static int bochs_get_edid_block(void *data, u8 *buf,
				unsigned int block, size_t len)
{
	struct bochs_device *bochs = data;
	size_t i, start = block * EDID_LENGTH;

	if (start + len > 0x400 /* vga register offset */)
		return -1;

	for (i = 0; i < len; i++) {
		buf[i] = readb(bochs->mmio + start + i);
	}
	return 0;
}