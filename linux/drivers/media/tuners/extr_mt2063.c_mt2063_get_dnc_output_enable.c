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
typedef  int /*<<< orphan*/  u32 ;
struct mt2063_state {int* reg; } ;
typedef  enum MT2063_DNC_Output_Enable { ____Placeholder_MT2063_DNC_Output_Enable } MT2063_DNC_Output_Enable ;

/* Variables and functions */
 int MT2063_DNC_1 ; 
 int MT2063_DNC_2 ; 
 int MT2063_DNC_BOTH ; 
 int MT2063_DNC_NONE ; 
 size_t MT2063_REG_DNC_GAIN ; 
 size_t MT2063_REG_VGA_GAIN ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static u32 mt2063_get_dnc_output_enable(struct mt2063_state *state,
					enum MT2063_DNC_Output_Enable *pValue)
{
	dprintk(2, "\n");

	if ((state->reg[MT2063_REG_DNC_GAIN] & 0x03) == 0x03) {	/* if DNC1 is off */
		if ((state->reg[MT2063_REG_VGA_GAIN] & 0x03) == 0x03)	/* if DNC2 is off */
			*pValue = MT2063_DNC_NONE;
		else
			*pValue = MT2063_DNC_2;
	} else {	/* DNC1 is on */
		if ((state->reg[MT2063_REG_VGA_GAIN] & 0x03) == 0x03)	/* if DNC2 is off */
			*pValue = MT2063_DNC_1;
		else
			*pValue = MT2063_DNC_BOTH;
	}
	return 0;
}