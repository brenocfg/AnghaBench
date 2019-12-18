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
struct CHIPSTATE {int dummy; } ;

/* Variables and functions */
 int TA8874Z_B0 ; 
 int TA8874Z_B1 ; 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int chip_read (struct CHIPSTATE*) ; 

__attribute__((used)) static int ta8874z_getrxsubchans(struct CHIPSTATE *chip)
{
	int val, mode;

	mode = V4L2_TUNER_SUB_MONO;

	val = chip_read(chip);
	if (val < 0)
		return mode;

	if (val & TA8874Z_B1){
		mode |= V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	}else if (!(val & TA8874Z_B0)){
		mode = V4L2_TUNER_SUB_STEREO;
	}
	/* v4l2_dbg(1, debug, &chip->sd,
		 "ta8874z_getrxsubchans(): raw chip read: 0x%02x, return: 0x%02x\n",
		 val, mode); */
	return mode;
}