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

/* Variables and functions */
 unsigned int BOOK3S_IRQPRIO_ALIGNMENT ; 
 unsigned int BOOK3S_IRQPRIO_ALTIVEC ; 
 unsigned int BOOK3S_IRQPRIO_DATA_SEGMENT ; 
 unsigned int BOOK3S_IRQPRIO_DATA_STORAGE ; 
 unsigned int BOOK3S_IRQPRIO_DEBUG ; 
 unsigned int BOOK3S_IRQPRIO_DECREMENTER ; 
 unsigned int BOOK3S_IRQPRIO_EXTERNAL ; 
 unsigned int BOOK3S_IRQPRIO_EXTERNAL_LEVEL ; 
 unsigned int BOOK3S_IRQPRIO_FAC_UNAVAIL ; 
 unsigned int BOOK3S_IRQPRIO_FP_UNAVAIL ; 
 unsigned int BOOK3S_IRQPRIO_INST_SEGMENT ; 
 unsigned int BOOK3S_IRQPRIO_INST_STORAGE ; 
 unsigned int BOOK3S_IRQPRIO_MACHINE_CHECK ; 
 unsigned int BOOK3S_IRQPRIO_MAX ; 
 unsigned int BOOK3S_IRQPRIO_PROGRAM ; 
 unsigned int BOOK3S_IRQPRIO_SYSCALL ; 
 unsigned int BOOK3S_IRQPRIO_SYSTEM_RESET ; 
 unsigned int BOOK3S_IRQPRIO_VSX ; 

__attribute__((used)) static int kvmppc_book3s_vec2irqprio(unsigned int vec)
{
	unsigned int prio;

	switch (vec) {
	case 0x100: prio = BOOK3S_IRQPRIO_SYSTEM_RESET;		break;
	case 0x200: prio = BOOK3S_IRQPRIO_MACHINE_CHECK;	break;
	case 0x300: prio = BOOK3S_IRQPRIO_DATA_STORAGE;		break;
	case 0x380: prio = BOOK3S_IRQPRIO_DATA_SEGMENT;		break;
	case 0x400: prio = BOOK3S_IRQPRIO_INST_STORAGE;		break;
	case 0x480: prio = BOOK3S_IRQPRIO_INST_SEGMENT;		break;
	case 0x500: prio = BOOK3S_IRQPRIO_EXTERNAL;		break;
	case 0x501: prio = BOOK3S_IRQPRIO_EXTERNAL_LEVEL;	break;
	case 0x600: prio = BOOK3S_IRQPRIO_ALIGNMENT;		break;
	case 0x700: prio = BOOK3S_IRQPRIO_PROGRAM;		break;
	case 0x800: prio = BOOK3S_IRQPRIO_FP_UNAVAIL;		break;
	case 0x900: prio = BOOK3S_IRQPRIO_DECREMENTER;		break;
	case 0xc00: prio = BOOK3S_IRQPRIO_SYSCALL;		break;
	case 0xd00: prio = BOOK3S_IRQPRIO_DEBUG;		break;
	case 0xf20: prio = BOOK3S_IRQPRIO_ALTIVEC;		break;
	case 0xf40: prio = BOOK3S_IRQPRIO_VSX;			break;
	case 0xf60: prio = BOOK3S_IRQPRIO_FAC_UNAVAIL;		break;
	default:    prio = BOOK3S_IRQPRIO_MAX;			break;
	}

	return prio;
}