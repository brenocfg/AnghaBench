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
typedef  scalar_t__ u32 ;
struct amdgpu_gpio_rec {scalar_t__ reg; int mask; } ;
struct amdgpu_hpd {void* hpd; struct amdgpu_gpio_rec gpio; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 void* AMDGPU_HPD_1 ; 
 void* AMDGPU_HPD_2 ; 
 void* AMDGPU_HPD_3 ; 
 void* AMDGPU_HPD_4 ; 
 void* AMDGPU_HPD_5 ; 
 void* AMDGPU_HPD_6 ; 
 void* AMDGPU_HPD_NONE ; 
 scalar_t__ amdgpu_display_hpd_get_gpio_reg (struct amdgpu_device*) ; 
 int /*<<< orphan*/  memset (struct amdgpu_hpd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct amdgpu_hpd
amdgpu_atombios_get_hpd_info_from_gpio(struct amdgpu_device *adev,
				       struct amdgpu_gpio_rec *gpio)
{
	struct amdgpu_hpd hpd;
	u32 reg;

	memset(&hpd, 0, sizeof(struct amdgpu_hpd));

	reg = amdgpu_display_hpd_get_gpio_reg(adev);

	hpd.gpio = *gpio;
	if (gpio->reg == reg) {
		switch(gpio->mask) {
		case (1 << 0):
			hpd.hpd = AMDGPU_HPD_1;
			break;
		case (1 << 8):
			hpd.hpd = AMDGPU_HPD_2;
			break;
		case (1 << 16):
			hpd.hpd = AMDGPU_HPD_3;
			break;
		case (1 << 24):
			hpd.hpd = AMDGPU_HPD_4;
			break;
		case (1 << 26):
			hpd.hpd = AMDGPU_HPD_5;
			break;
		case (1 << 28):
			hpd.hpd = AMDGPU_HPD_6;
			break;
		default:
			hpd.hpd = AMDGPU_HPD_NONE;
			break;
		}
	} else
		hpd.hpd = AMDGPU_HPD_NONE;
	return hpd;
}