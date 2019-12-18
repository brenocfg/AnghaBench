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
struct ov965x {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 int REG_GSP ; 
 int ov965x_write (struct ov965x*,int,int const) ; 

__attribute__((used)) static int ov965x_set_default_gamma_curve(struct ov965x *ov965x)
{
	static const u8 gamma_curve[] = {
		/* Values taken from OV application note. */
		0x40, 0x30, 0x4b, 0x60, 0x70, 0x70, 0x70, 0x70,
		0x60, 0x60, 0x50, 0x48, 0x3a, 0x2e, 0x28, 0x22,
		0x04, 0x07, 0x10, 0x28,	0x36, 0x44, 0x52, 0x60,
		0x6c, 0x78, 0x8c, 0x9e, 0xbb, 0xd2, 0xe6
	};
	u8 addr = REG_GSP;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(gamma_curve); i++) {
		int ret = ov965x_write(ov965x, addr, gamma_curve[i]);

		if (ret < 0)
			return ret;
		addr++;
	}

	return 0;
}