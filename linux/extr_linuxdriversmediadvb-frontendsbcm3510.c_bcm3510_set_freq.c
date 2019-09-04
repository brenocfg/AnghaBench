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
struct bcm3510_state {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int bcm3510_tuner_cmd (struct bcm3510_state*,int,int,int) ; 
 int /*<<< orphan*/  deb_info (char*,int,...) ; 

__attribute__((used)) static int bcm3510_set_freq(struct bcm3510_state* st,u32 freq)
{
	u8 bc,a;
	u16 n;
	s32 YIntercept,Tfvco1;

	freq /= 1000;

	deb_info("%dkHz:",freq);
	/* set Band Switch */
	if (freq <= 168000)
		bc = 0x1c;
	else if (freq <= 378000)
		bc = 0x2c;
	else
		bc = 0x30;

	if (freq >= 470000) {
		freq -= 470001;
		YIntercept = 18805;
	} else if (freq >= 90000) {
		freq -= 90001;
		YIntercept = 15005;
	} else if (freq >= 76000){
		freq -= 76001;
		YIntercept = 14865;
	} else {
		freq -= 54001;
		YIntercept = 14645;
	}

	Tfvco1 = (((freq/6000)*60 + YIntercept)*4)/10;

	n = Tfvco1 >> 6;
	a = Tfvco1 & 0x3f;

	deb_info(" BC1_2_3_4: %x, N: %x A: %x\n", bc, n, a);
	if (n >= 16 && n <= 2047)
		return bcm3510_tuner_cmd(st,bc,n,a);

	return -EINVAL;
}