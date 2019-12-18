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
typedef  scalar_t__ u32 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_volt {int vidmask; int ranged; int base; int step; int min; int max; int pwm_freq; int pwm_range; void* type; } ;

/* Variables and functions */
 void* NVBIOS_VOLT_GPIO ; 
 void* NVBIOS_VOLT_PWM ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memset (struct nvbios_volt*,int,int) ; 
 int min (int,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 void* nvbios_rd16 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 
 scalar_t__ nvbios_volt_table (struct nvkm_bios*,int*,int*,int*,int*) ; 

u32
nvbios_volt_parse(struct nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		  struct nvbios_volt *info)
{
	u32 volt = nvbios_volt_table(bios, ver, hdr, cnt, len);
	memset(info, 0x00, sizeof(*info));
	switch (!!volt * *ver) {
	case 0x12:
		info->type    = NVBIOS_VOLT_GPIO;
		info->vidmask = nvbios_rd08(bios, volt + 0x04);
		info->ranged  = false;
		break;
	case 0x20:
		info->type    = NVBIOS_VOLT_GPIO;
		info->vidmask = nvbios_rd08(bios, volt + 0x05);
		info->ranged  = false;
		break;
	case 0x30:
		info->type    = NVBIOS_VOLT_GPIO;
		info->vidmask = nvbios_rd08(bios, volt + 0x04);
		info->ranged  = false;
		break;
	case 0x40:
		info->type    = NVBIOS_VOLT_GPIO;
		info->base    = nvbios_rd32(bios, volt + 0x04);
		info->step    = nvbios_rd16(bios, volt + 0x08);
		info->vidmask = nvbios_rd08(bios, volt + 0x0b);
		info->ranged  = true; /* XXX: find the flag byte */
		info->min     = min(info->base,
				    info->base + info->step * info->vidmask);
		info->max     = nvbios_rd32(bios, volt + 0x0e);
		if (!info->max)
			info->max = max(info->base, info->base + info->step * info->vidmask);
		break;
	case 0x50:
		info->min     = nvbios_rd32(bios, volt + 0x0a);
		info->max     = nvbios_rd32(bios, volt + 0x0e);
		info->base    = nvbios_rd32(bios, volt + 0x12) & 0x00ffffff;

		/* offset 4 seems to be a flag byte */
		if (nvbios_rd32(bios, volt + 0x4) & 1) {
			info->type      = NVBIOS_VOLT_PWM;
			info->pwm_freq  = nvbios_rd32(bios, volt + 0x5) / 1000;
			info->pwm_range = nvbios_rd32(bios, volt + 0x16);
		} else {
			info->type    = NVBIOS_VOLT_GPIO;
			info->vidmask = nvbios_rd08(bios, volt + 0x06);
			info->step    = nvbios_rd16(bios, volt + 0x16);
			info->ranged  =
				!!(nvbios_rd08(bios, volt + 0x4) & 0x2);
		}
		break;
	}
	return volt;
}