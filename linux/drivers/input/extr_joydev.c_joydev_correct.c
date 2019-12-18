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
struct js_corr {int type; int* coef; } ;

/* Variables and functions */
#define  JS_CORR_BROKEN 129 
#define  JS_CORR_NONE 128 
 int clamp (int,int,int) ; 

__attribute__((used)) static int joydev_correct(int value, struct js_corr *corr)
{
	switch (corr->type) {

	case JS_CORR_NONE:
		break;

	case JS_CORR_BROKEN:
		value = value > corr->coef[0] ? (value < corr->coef[1] ? 0 :
			((corr->coef[3] * (value - corr->coef[1])) >> 14)) :
			((corr->coef[2] * (value - corr->coef[0])) >> 14);
		break;

	default:
		return 0;
	}

	return clamp(value, -32767, 32767);
}