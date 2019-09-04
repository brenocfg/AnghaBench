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

__attribute__((used)) static void core99_nvram_write_byte(int addr, unsigned char val)
{
	if (nvram_image == NULL)
		return;
	nvram_image[addr] = val;
}