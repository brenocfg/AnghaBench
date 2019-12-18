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
struct si470x_device {int band; int* registers; int (* set_register ) (struct si470x_device*,size_t) ;} ;

/* Variables and functions */
 size_t SYSCONFIG2 ; 
 int SYSCONFIG2_BAND ; 
 int stub1 (struct si470x_device*,size_t) ; 

__attribute__((used)) static int si470x_set_band(struct si470x_device *radio, int band)
{
	if (radio->band == band)
		return 0;

	radio->band = band;
	radio->registers[SYSCONFIG2] &= ~SYSCONFIG2_BAND;
	radio->registers[SYSCONFIG2] |= radio->band << 6;
	return radio->set_register(radio, SYSCONFIG2);
}