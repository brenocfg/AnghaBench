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
struct si470x_device {int* registers; } ;

/* Variables and functions */
 size_t SYSCONFIG2 ; 
 int SYSCONFIG2_SPACE ; 

__attribute__((used)) static unsigned int si470x_get_step(struct si470x_device *radio)
{
	/* Spacing (kHz) */
	switch ((radio->registers[SYSCONFIG2] & SYSCONFIG2_SPACE) >> 4) {
	/* 0: 200 kHz (USA, Australia) */
	case 0:
		return 200 * 16;
	/* 1: 100 kHz (Europe, Japan) */
	case 1:
		return 100 * 16;
	/* 2:  50 kHz */
	default:
		return 50 * 16;
	}
}