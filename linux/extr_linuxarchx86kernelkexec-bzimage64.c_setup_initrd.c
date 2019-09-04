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
struct TYPE_2__ {unsigned long ramdisk_image; unsigned long ramdisk_size; } ;
struct boot_params {unsigned long ext_ramdisk_image; unsigned long ext_ramdisk_size; TYPE_1__ hdr; } ;

/* Variables and functions */

__attribute__((used)) static int setup_initrd(struct boot_params *params,
		unsigned long initrd_load_addr, unsigned long initrd_len)
{
	params->hdr.ramdisk_image = initrd_load_addr & 0xffffffffUL;
	params->hdr.ramdisk_size = initrd_len & 0xffffffffUL;

	params->ext_ramdisk_image = initrd_load_addr >> 32;
	params->ext_ramdisk_size = initrd_len >> 32;

	return 0;
}