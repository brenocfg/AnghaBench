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
 unsigned char GAYLE_CFG_0V ; 
 unsigned char GAYLE_CFG_12V ; 
 unsigned char GAYLE_CFG_5V ; 
#define  PCMCIA_0V 130 
#define  PCMCIA_12V 129 
#define  PCMCIA_5V 128 
 int cfg_byte ; 
 TYPE_1__ gayle ; 

void pcmcia_program_voltage(int voltage)
{
	unsigned char v;

	switch (voltage) {
	case PCMCIA_0V:
		v = GAYLE_CFG_0V;
		break;
	case PCMCIA_5V:
		v = GAYLE_CFG_5V;
		break;
	case PCMCIA_12V:
		v = GAYLE_CFG_12V;
		break;
	default:
		v = GAYLE_CFG_0V;
	}

	cfg_byte = (cfg_byte & 0xfc) | v;
	gayle.config = cfg_byte;

}