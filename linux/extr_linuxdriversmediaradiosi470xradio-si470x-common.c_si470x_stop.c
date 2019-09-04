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
struct si470x_device {int* registers; int (* set_register ) (struct si470x_device*,size_t) ;} ;

/* Variables and functions */
 size_t POWERCFG ; 
 int POWERCFG_DISABLE ; 
 int POWERCFG_DMUTE ; 
 int POWERCFG_ENABLE ; 
 size_t SYSCONFIG1 ; 
 int SYSCONFIG1_RDS ; 
 int stub1 (struct si470x_device*,size_t) ; 
 int stub2 (struct si470x_device*,size_t) ; 

int si470x_stop(struct si470x_device *radio)
{
	int retval;

	/* sysconfig 1 */
	radio->registers[SYSCONFIG1] &= ~SYSCONFIG1_RDS;
	retval = radio->set_register(radio, SYSCONFIG1);
	if (retval < 0)
		goto done;

	/* powercfg */
	radio->registers[POWERCFG] &= ~POWERCFG_DMUTE;
	/* POWERCFG_ENABLE has to automatically go low */
	radio->registers[POWERCFG] |= POWERCFG_ENABLE |	POWERCFG_DISABLE;
	retval = radio->set_register(radio, POWERCFG);

done:
	return retval;
}