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
typedef  int ushort ;

/* Variables and functions */
 int dos_encode_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dos_encode_block(ushort *dest, unsigned char *src, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		*dest=dos_encode_byte(*src++);
		*dest|=((dest[-1]&1)||(*dest&0x4000))? 0: 0x8000;
		dest++;
	}
}