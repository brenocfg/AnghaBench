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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_bios {int bmp_offset; struct nvkm_subdev subdev; } ;
struct dcb_i2c_entry {int type; int drive; int sense; int share; int auxch; } ;

/* Variables and functions */
#define  DCB_I2C_NV04_BIT 133 
#define  DCB_I2C_NV4E_BIT 132 
#define  DCB_I2C_NVIO_AUX 131 
#define  DCB_I2C_NVIO_BIT 130 
#define  DCB_I2C_PMGR 129 
#define  DCB_I2C_UNUSED 128 
 int ENOENT ; 
 int dcb_i2c_entry (struct nvkm_bios*,int,int*,int*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd32 (struct nvkm_bios*,int) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int) ; 

int
dcb_i2c_parse(struct nvkm_bios *bios, u8 idx, struct dcb_i2c_entry *info)
{
	struct nvkm_subdev *subdev = &bios->subdev;
	u8  ver, len;
	u16 ent = dcb_i2c_entry(bios, idx, &ver, &len);
	if (ent) {
		if (ver >= 0x41) {
			u32 ent_value = nvbios_rd32(bios, ent);
			u8 i2c_port = (ent_value >> 0) & 0x1f;
			u8 dpaux_port = (ent_value >> 5) & 0x1f;
			/* value 0x1f means unused according to DCB 4.x spec */
			if (i2c_port == 0x1f && dpaux_port == 0x1f)
				info->type = DCB_I2C_UNUSED;
			else
				info->type = DCB_I2C_PMGR;
		} else
		if (ver >= 0x30) {
			info->type = nvbios_rd08(bios, ent + 0x03);
		} else {
			info->type = nvbios_rd08(bios, ent + 0x03) & 0x07;
			if (info->type == 0x07)
				info->type = DCB_I2C_UNUSED;
		}

		info->drive = DCB_I2C_UNUSED;
		info->sense = DCB_I2C_UNUSED;
		info->share = DCB_I2C_UNUSED;
		info->auxch = DCB_I2C_UNUSED;

		switch (info->type) {
		case DCB_I2C_NV04_BIT:
			info->drive = nvbios_rd08(bios, ent + 0);
			info->sense = nvbios_rd08(bios, ent + 1);
			return 0;
		case DCB_I2C_NV4E_BIT:
			info->drive = nvbios_rd08(bios, ent + 1);
			return 0;
		case DCB_I2C_NVIO_BIT:
			info->drive = nvbios_rd08(bios, ent + 0) & 0x0f;
			if (nvbios_rd08(bios, ent + 1) & 0x01)
				info->share = nvbios_rd08(bios, ent + 1) >> 1;
			return 0;
		case DCB_I2C_NVIO_AUX:
			info->auxch = nvbios_rd08(bios, ent + 0) & 0x0f;
			if (nvbios_rd08(bios, ent + 1) & 0x01)
					info->share = info->auxch;
			return 0;
		case DCB_I2C_PMGR:
			info->drive = (nvbios_rd16(bios, ent + 0) & 0x01f) >> 0;
			if (info->drive == 0x1f)
				info->drive = DCB_I2C_UNUSED;
			info->auxch = (nvbios_rd16(bios, ent + 0) & 0x3e0) >> 5;
			if (info->auxch == 0x1f)
				info->auxch = DCB_I2C_UNUSED;
			info->share = info->auxch;
			return 0;
		case DCB_I2C_UNUSED:
			return 0;
		default:
			nvkm_warn(subdev, "unknown i2c type %d\n", info->type);
			info->type = DCB_I2C_UNUSED;
			return 0;
		}
	}

	if (bios->bmp_offset && idx < 2) {
		/* BMP (from v4.0 has i2c info in the structure, it's in a
		 * fixed location on earlier VBIOS
		 */
		if (nvbios_rd08(bios, bios->bmp_offset + 5) < 4)
			ent = 0x0048;
		else
			ent = 0x0036 + bios->bmp_offset;

		if (idx == 0) {
			info->drive = nvbios_rd08(bios, ent + 4);
			if (!info->drive) info->drive = 0x3f;
			info->sense = nvbios_rd08(bios, ent + 5);
			if (!info->sense) info->sense = 0x3e;
		} else
		if (idx == 1) {
			info->drive = nvbios_rd08(bios, ent + 6);
			if (!info->drive) info->drive = 0x37;
			info->sense = nvbios_rd08(bios, ent + 7);
			if (!info->sense) info->sense = 0x36;
		}

		info->type  = DCB_I2C_NV04_BIT;
		info->share = DCB_I2C_UNUSED;
		return 0;
	}

	return -ENOENT;
}