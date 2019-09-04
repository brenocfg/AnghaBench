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

/* Variables and functions */
 unsigned char* nvram_image ; 

__attribute__((used)) static unsigned char core99_nvram_read_byte(int addr)
{
	if (nvram_image == NULL)
		return 0xff;
	return nvram_image[addr];
}