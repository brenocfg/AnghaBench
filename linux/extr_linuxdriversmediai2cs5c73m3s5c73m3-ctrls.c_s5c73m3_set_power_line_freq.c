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
struct s5c73m3 {int dummy; } ;

/* Variables and functions */
 unsigned int COMM_FLICKER_AUTO_50HZ ; 
 unsigned int COMM_FLICKER_AUTO_60HZ ; 
 int /*<<< orphan*/  COMM_FLICKER_MODE ; 
 unsigned int COMM_FLICKER_NONE ; 
#define  V4L2_CID_POWER_LINE_FREQUENCY_50HZ 131 
#define  V4L2_CID_POWER_LINE_FREQUENCY_60HZ 130 
#define  V4L2_CID_POWER_LINE_FREQUENCY_AUTO 129 
#define  V4L2_CID_POWER_LINE_FREQUENCY_DISABLED 128 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int s5c73m3_set_power_line_freq(struct s5c73m3 *state, int val)
{
	unsigned int pwr_line_freq = COMM_FLICKER_NONE;

	switch (val) {
	case V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		pwr_line_freq = COMM_FLICKER_NONE;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
		pwr_line_freq = COMM_FLICKER_AUTO_50HZ;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		pwr_line_freq = COMM_FLICKER_AUTO_60HZ;
		break;
	default:
	case V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
		pwr_line_freq = COMM_FLICKER_NONE;
	}

	return s5c73m3_isp_command(state, COMM_FLICKER_MODE, pwr_line_freq);
}