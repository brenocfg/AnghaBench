#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int config; } ;

/* Variables and functions */
 unsigned char GAYLE_CFG_100NS ; 
 unsigned char GAYLE_CFG_150NS ; 
 unsigned char GAYLE_CFG_250NS ; 
 unsigned char GAYLE_CFG_720NS ; 
 int PCMCIA_SPEED_100NS ; 
 int PCMCIA_SPEED_150NS ; 
 int PCMCIA_SPEED_250NS ; 
 int cfg_byte ; 
 TYPE_1__ gayle ; 

void pcmcia_access_speed(int speed)
{
	unsigned char s;

	if (speed <= PCMCIA_SPEED_100NS)
		s = GAYLE_CFG_100NS;
	else if (speed <= PCMCIA_SPEED_150NS)
		s = GAYLE_CFG_150NS;
	else if (speed <= PCMCIA_SPEED_250NS)
		s = GAYLE_CFG_250NS;
	else
		s = GAYLE_CFG_720NS;

	cfg_byte = (cfg_byte & 0xf3) | s;
	gayle.config = cfg_byte;
}