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
typedef  int u8 ;
typedef  int u32 ;
struct mt2063_state {int* reg; size_t rcvr_mode; } ;
typedef  enum MT2063_DNC_Output_Enable { ____Placeholder_MT2063_DNC_Output_Enable } MT2063_DNC_Output_Enable ;

/* Variables and functions */
 int* DNC1GC ; 
 int* DNC2GC ; 
#define  MT2063_DNC_1 131 
#define  MT2063_DNC_2 130 
#define  MT2063_DNC_BOTH 129 
#define  MT2063_DNC_NONE 128 
 size_t MT2063_REG_DNC_GAIN ; 
 size_t MT2063_REG_RSVD_20 ; 
 size_t MT2063_REG_VGA_GAIN ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int mt2063_setreg (struct mt2063_state*,size_t,int) ; 

__attribute__((used)) static u32 mt2063_set_dnc_output_enable(struct mt2063_state *state,
					enum MT2063_DNC_Output_Enable nValue)
{
	int status = 0;	/* Status to be returned        */
	u8 val = 0;

	dprintk(2, "\n");

	/* selects, which DNC output is used */
	switch (nValue) {
	case MT2063_DNC_NONE:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | 0x03;	/* Set DNC1GC=3 */
		if (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | 0x03;	/* Set DNC2GC=3 */
		if (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] & ~0x40);	/* Set PD2MUX=0 */
		if (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		break;
	case MT2063_DNC_1:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | (DNC1GC[state->rcvr_mode] & 0x03);	/* Set DNC1GC=x */
		if (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | 0x03;	/* Set DNC2GC=3 */
		if (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] & ~0x40);	/* Set PD2MUX=0 */
		if (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		break;
	case MT2063_DNC_2:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | 0x03;	/* Set DNC1GC=3 */
		if (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | (DNC2GC[state->rcvr_mode] & 0x03);	/* Set DNC2GC=x */
		if (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] | 0x40);	/* Set PD2MUX=1 */
		if (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		break;
	case MT2063_DNC_BOTH:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | (DNC1GC[state->rcvr_mode] & 0x03);	/* Set DNC1GC=x */
		if (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | (DNC2GC[state->rcvr_mode] & 0x03);	/* Set DNC2GC=x */
		if (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] | 0x40);	/* Set PD2MUX=1 */
		if (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		break;
	default:
		break;
	}

	return status;
}