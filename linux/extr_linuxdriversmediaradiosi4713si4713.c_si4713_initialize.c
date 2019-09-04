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
struct si4713_device {int stereo; int /*<<< orphan*/  tune_rnl; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FREQUENCY ; 
 int /*<<< orphan*/  DEFAULT_TUNE_RNL ; 
 int /*<<< orphan*/  POWER_OFF ; 
 int /*<<< orphan*/  POWER_ON ; 
 int si4713_checkrev (struct si4713_device*) ; 
 int si4713_set_power_state (struct si4713_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_initialize(struct si4713_device *sdev)
{
	int rval;

	rval = si4713_set_power_state(sdev, POWER_ON);
	if (rval < 0)
		return rval;

	rval = si4713_checkrev(sdev);
	if (rval < 0)
		return rval;

	rval = si4713_set_power_state(sdev, POWER_OFF);
	if (rval < 0)
		return rval;

	sdev->frequency = DEFAULT_FREQUENCY;
	sdev->stereo = 1;
	sdev->tune_rnl = DEFAULT_TUNE_RNL;
	return 0;
}