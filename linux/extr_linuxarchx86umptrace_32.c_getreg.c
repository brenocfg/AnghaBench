#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long* gp; } ;
struct TYPE_5__ {TYPE_1__ regs; } ;
struct TYPE_6__ {TYPE_2__ regs; } ;
struct task_struct {TYPE_3__ thread; } ;

/* Variables and functions */
#define  CS 144 
#define  DS 143 
#define  EAX 142 
#define  EBP 141 
#define  EBX 140 
#define  ECX 139 
#define  EDI 138 
#define  EDX 137 
#define  EFL 136 
#define  EIP 135 
#define  ES 134 
#define  ESI 133 
#define  FS 132 
#define  GS 131 
#define  ORIG_EAX 130 
#define  SS 129 
#define  UESP 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 size_t* reg_offsets ; 

unsigned long getreg(struct task_struct *child, int regno)
{
	unsigned long mask = ~0UL;

	regno >>= 2;
	switch (regno) {
	case FS:
	case GS:
	case DS:
	case ES:
	case SS:
	case CS:
		mask = 0xffff;
		break;
	case EIP:
	case UESP:
	case EAX:
	case EBX:
	case ECX:
	case EDX:
	case ESI:
	case EDI:
	case EBP:
	case EFL:
	case ORIG_EAX:
		break;
	default:
		panic("Bad register in getreg() : %d\n", regno);
	}
	return mask & child->thread.regs.regs.gp[reg_offsets[regno]];
}