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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_i2c_pad {int id; TYPE_1__* i2c; } ;
struct nvkm_device {int dummy; } ;
typedef  enum nvkm_i2c_pad_mode { ____Placeholder_nvkm_i2c_pad_mode } nvkm_i2c_pad_mode ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;

/* Variables and functions */
#define  NVKM_I2C_PAD_AUX 130 
 int NVKM_I2C_PAD_HYBRID (int /*<<< orphan*/ ) ; 
#define  NVKM_I2C_PAD_I2C 129 
#define  NVKM_I2C_PAD_OFF 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
gm200_i2c_pad_mode(struct nvkm_i2c_pad *pad, enum nvkm_i2c_pad_mode mode)
{
	struct nvkm_subdev *subdev = &pad->i2c->subdev;
	struct nvkm_device *device = subdev->device;
	const u32 base = (pad->id - NVKM_I2C_PAD_HYBRID(0)) * 0x50;

	switch (mode) {
	case NVKM_I2C_PAD_OFF:
		nvkm_mask(device, 0x00d97c + base, 0x00000001, 0x00000001);
		break;
	case NVKM_I2C_PAD_I2C:
		nvkm_mask(device, 0x00d970 + base, 0x0000c003, 0x0000c001);
		nvkm_mask(device, 0x00d97c + base, 0x00000001, 0x00000000);
		break;
	case NVKM_I2C_PAD_AUX:
		nvkm_mask(device, 0x00d970 + base, 0x0000c003, 0x00000002);
		nvkm_mask(device, 0x00d97c + base, 0x00000001, 0x00000000);
		break;
	default:
		WARN_ON(1);
		break;
	}
}