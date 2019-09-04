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
struct nvbios_therm_fan {int pwm_freq; void* max_duty; void* min_duty; int /*<<< orphan*/  fan_mode; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVBIOS_THERM_FAN_LINEAR ; 
 int /*<<< orphan*/  NVBIOS_THERM_FAN_PWM ; 
 int /*<<< orphan*/  NVBIOS_THERM_FAN_TOGGLE ; 
 int /*<<< orphan*/  NVBIOS_THERM_FAN_UNK ; 
 scalar_t__ nvbios_fan_entry (struct nvkm_bios*,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 void* nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int nvbios_rd32 (struct nvkm_bios*,scalar_t__) ; 

u32
nvbios_fan_parse(struct nvkm_bios *bios, struct nvbios_therm_fan *fan)
{
	u8 ver, hdr, cnt, len;

	u32 data = nvbios_fan_entry(bios, 0, &ver, &hdr, &cnt, &len);
	if (data) {
		u8 type = nvbios_rd08(bios, data + 0x00);
		switch (type) {
		case 0:
			fan->type = NVBIOS_THERM_FAN_TOGGLE;
			break;
		case 1:
		case 2:
			/* TODO: Understand the difference between the two! */
			fan->type = NVBIOS_THERM_FAN_PWM;
			break;
		default:
			fan->type = NVBIOS_THERM_FAN_UNK;
		}

		fan->fan_mode = NVBIOS_THERM_FAN_LINEAR;
		fan->min_duty = nvbios_rd08(bios, data + 0x02);
		fan->max_duty = nvbios_rd08(bios, data + 0x03);

		fan->pwm_freq = nvbios_rd32(bios, data + 0x0b) & 0xffffff;
	}

	return data;
}