#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_6__ {int sigh; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_OVER ; 
 int /*<<< orphan*/  FPU_Special (TYPE_1__*) ; 
 scalar_t__ SIGN_NEG ; 
 int SW_C0 ; 
 int SW_C1 ; 
 int SW_C2 ; 
 int SW_C3 ; 
#define  TAG_Empty 134 
#define  TAG_Special 133 
#define  TAG_Valid 132 
#define  TAG_Zero 131 
#define  TW_Denormal 130 
#define  TW_Infinity 129 
#define  TW_NaN 128 
 int /*<<< orphan*/  exponent (TYPE_1__*) ; 
 scalar_t__ getsign (TYPE_1__*) ; 
 int /*<<< orphan*/  setcc (int) ; 

__attribute__((used)) static void fxam(FPU_REG *st0_ptr, u_char st0tag)
{
	int c = 0;
	switch (st0tag) {
	case TAG_Empty:
		c = SW_C3 | SW_C0;
		break;
	case TAG_Zero:
		c = SW_C3;
		break;
	case TAG_Valid:
		c = SW_C2;
		break;
	case TAG_Special:
		switch (FPU_Special(st0_ptr)) {
		case TW_Denormal:
			c = SW_C2 | SW_C3;	/* Denormal */
			break;
		case TW_NaN:
			/* We also use NaN for unsupported types. */
			if ((st0_ptr->sigh & 0x80000000)
			    && (exponent(st0_ptr) == EXP_OVER))
				c = SW_C0;
			break;
		case TW_Infinity:
			c = SW_C2 | SW_C0;
			break;
		}
	}
	if (getsign(st0_ptr) == SIGN_NEG)
		c |= SW_C1;
	setcc(c);
}