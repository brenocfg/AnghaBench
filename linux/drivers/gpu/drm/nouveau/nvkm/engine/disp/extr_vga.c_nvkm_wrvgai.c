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
typedef  int u16 ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wrvgac (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wrvgag (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wrvgas (struct nvkm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nvkm_wrvgai(struct nvkm_device *device, int head, u16 port, u8 index, u8 value)
{
	if      (port == 0x03c4) nvkm_wrvgas(device, head, index, value);
	else if (port == 0x03ce) nvkm_wrvgag(device, head, index, value);
	else if (port == 0x03d4) nvkm_wrvgac(device, head, index, value);
}