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
typedef  int uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_STEREO_CURRENT_EYE ; 
 int /*<<< orphan*/  OTG_STEREO_STATUS ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

bool optc1_is_stereo_left_eye(struct timing_generator *optc)
{
	bool ret = false;
	uint32_t left_eye = 0;
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_GET(OTG_STEREO_STATUS,
		OTG_STEREO_CURRENT_EYE, &left_eye);
	if (left_eye == 1)
		ret = true;
	else
		ret = false;

	return ret;
}