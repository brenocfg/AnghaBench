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
 int TDA985x_SAPP ; 
 int TDA985x_STP ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_SAP ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int chip_read (struct CHIPSTATE*) ; 

__attribute__((used)) static int  tda985x_getrxsubchans(struct CHIPSTATE *chip)
{
	int mode, val;

	/* Add mono mode regardless of SAP and stereo */
	/* Allows forced mono */
	mode = V4L2_TUNER_SUB_MONO;
	val = chip_read(chip);
	if (val < 0)
		return mode;

	if (val & TDA985x_STP)
		mode = V4L2_TUNER_SUB_STEREO;
	if (val & TDA985x_SAPP)
		mode |= V4L2_TUNER_SUB_SAP;
	return mode;
}