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
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wrport (struct nvkm_device*,int,int,int /*<<< orphan*/ ) ; 

void
nvkm_wrvgas(struct nvkm_device *device, int head, u8 index, u8 value)
{
	nvkm_wrport(device, head, 0x03c4, index);
	nvkm_wrport(device, head, 0x03c5, value);
}