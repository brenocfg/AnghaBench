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
struct si470x_device {int* registers; int (* set_register ) (struct si470x_device*,size_t) ;int band; } ;

/* Variables and functions */
 size_t CHANNEL ; 
 int CHANNEL_CHAN ; 
 size_t POWERCFG ; 
 int POWERCFG_DMUTE ; 
 int POWERCFG_ENABLE ; 
 int POWERCFG_RDSM ; 
 size_t SYSCONFIG1 ; 
 int SYSCONFIG1_DE ; 
 int SYSCONFIG1_GPIO2 ; 
 int SYSCONFIG1_GPIO2_INT ; 
 int SYSCONFIG1_RDS ; 
 int SYSCONFIG1_RDSIEN ; 
 int SYSCONFIG1_STCIEN ; 
 size_t SYSCONFIG2 ; 
 int SYSCONFIG2_BAND ; 
 int SYSCONFIG2_SPACE ; 
 scalar_t__ de ; 
 int si470x_set_chan (struct si470x_device*,int) ; 
 int space ; 
 int stub1 (struct si470x_device*,size_t) ; 
 int stub2 (struct si470x_device*,size_t) ; 
 int stub3 (struct si470x_device*,size_t) ; 

int si470x_start(struct si470x_device *radio)
{
	int retval;

	/* powercfg */
	radio->registers[POWERCFG] =
		POWERCFG_DMUTE | POWERCFG_ENABLE | POWERCFG_RDSM;
	retval = radio->set_register(radio, POWERCFG);
	if (retval < 0)
		goto done;

	/* sysconfig 1 */
	radio->registers[SYSCONFIG1] |= SYSCONFIG1_RDSIEN | SYSCONFIG1_STCIEN |
					SYSCONFIG1_RDS;
	radio->registers[SYSCONFIG1] &= ~SYSCONFIG1_GPIO2;
	radio->registers[SYSCONFIG1] |= SYSCONFIG1_GPIO2_INT;
	if (de)
		radio->registers[SYSCONFIG1] |= SYSCONFIG1_DE;
	retval = radio->set_register(radio, SYSCONFIG1);
	if (retval < 0)
		goto done;

	/* sysconfig 2 */
	radio->registers[SYSCONFIG2] =
		(0x1f  << 8) |				/* SEEKTH */
		((radio->band << 6) & SYSCONFIG2_BAND) |/* BAND */
		((space << 4) & SYSCONFIG2_SPACE) |	/* SPACE */
		15;					/* VOLUME (max) */
	retval = radio->set_register(radio, SYSCONFIG2);
	if (retval < 0)
		goto done;

	/* reset last channel */
	retval = si470x_set_chan(radio,
		radio->registers[CHANNEL] & CHANNEL_CHAN);

done:
	return retval;
}