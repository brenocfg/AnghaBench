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
struct nvkm_device {int chipset; } ;

/* Variables and functions */

__attribute__((used)) static int
nv40_gr_vs_count(struct nvkm_device *device)
{

	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		return 8;
	case 0x40:
		return 6;
	case 0x41:
	case 0x42:
		return 5;
	case 0x43:
	case 0x44:
	case 0x46:
	case 0x4a:
		return 3;
	case 0x4c:
	case 0x4e:
	case 0x67:
	default:
		return 1;
	}
}