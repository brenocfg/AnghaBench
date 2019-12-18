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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tlv320aic23b_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static int tlv320aic23b_s_clock_freq(struct v4l2_subdev *sd, u32 freq)
{
	switch (freq) {
	case 32000: /* set sample rate to 32 kHz */
		tlv320aic23b_write(sd, 8, 0x018);
		break;
	case 44100: /* set sample rate to 44.1 kHz */
		tlv320aic23b_write(sd, 8, 0x022);
		break;
	case 48000: /* set sample rate to 48 kHz */
		tlv320aic23b_write(sd, 8, 0x000);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}