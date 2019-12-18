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
struct v4l2_fract {int numerator; int denominator; } ;

/* Variables and functions */
 int CODA_FRATE_DIV_OFFSET ; 

__attribute__((used)) static uint32_t coda_timeperframe_to_frate(struct v4l2_fract *timeperframe)
{
	return ((timeperframe->numerator - 1) << CODA_FRATE_DIV_OFFSET) |
		timeperframe->denominator;
}