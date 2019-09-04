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
typedef  int /*<<< orphan*/  u16 ;
struct mxl5005s_state {TYPE_1__* TunerRegs; int /*<<< orphan*/  TunerRegs_Num; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;
struct TYPE_2__ {int Reg_Num; int Reg_Val; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_REGS_NUM ; 

__attribute__((used)) static u16 MXL5005_RegisterInit(struct dvb_frontend *fe)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	state->TunerRegs_Num = TUNER_REGS_NUM ;

	state->TunerRegs[0].Reg_Num = 9 ;
	state->TunerRegs[0].Reg_Val = 0x40 ;

	state->TunerRegs[1].Reg_Num = 11 ;
	state->TunerRegs[1].Reg_Val = 0x19 ;

	state->TunerRegs[2].Reg_Num = 12 ;
	state->TunerRegs[2].Reg_Val = 0x60 ;

	state->TunerRegs[3].Reg_Num = 13 ;
	state->TunerRegs[3].Reg_Val = 0x00 ;

	state->TunerRegs[4].Reg_Num = 14 ;
	state->TunerRegs[4].Reg_Val = 0x00 ;

	state->TunerRegs[5].Reg_Num = 15 ;
	state->TunerRegs[5].Reg_Val = 0xC0 ;

	state->TunerRegs[6].Reg_Num = 16 ;
	state->TunerRegs[6].Reg_Val = 0x00 ;

	state->TunerRegs[7].Reg_Num = 17 ;
	state->TunerRegs[7].Reg_Val = 0x00 ;

	state->TunerRegs[8].Reg_Num = 18 ;
	state->TunerRegs[8].Reg_Val = 0x00 ;

	state->TunerRegs[9].Reg_Num = 19 ;
	state->TunerRegs[9].Reg_Val = 0x34 ;

	state->TunerRegs[10].Reg_Num = 21 ;
	state->TunerRegs[10].Reg_Val = 0x00 ;

	state->TunerRegs[11].Reg_Num = 22 ;
	state->TunerRegs[11].Reg_Val = 0x6B ;

	state->TunerRegs[12].Reg_Num = 23 ;
	state->TunerRegs[12].Reg_Val = 0x35 ;

	state->TunerRegs[13].Reg_Num = 24 ;
	state->TunerRegs[13].Reg_Val = 0x70 ;

	state->TunerRegs[14].Reg_Num = 25 ;
	state->TunerRegs[14].Reg_Val = 0x3E ;

	state->TunerRegs[15].Reg_Num = 26 ;
	state->TunerRegs[15].Reg_Val = 0x82 ;

	state->TunerRegs[16].Reg_Num = 31 ;
	state->TunerRegs[16].Reg_Val = 0x00 ;

	state->TunerRegs[17].Reg_Num = 32 ;
	state->TunerRegs[17].Reg_Val = 0x40 ;

	state->TunerRegs[18].Reg_Num = 33 ;
	state->TunerRegs[18].Reg_Val = 0x53 ;

	state->TunerRegs[19].Reg_Num = 34 ;
	state->TunerRegs[19].Reg_Val = 0x81 ;

	state->TunerRegs[20].Reg_Num = 35 ;
	state->TunerRegs[20].Reg_Val = 0xC9 ;

	state->TunerRegs[21].Reg_Num = 36 ;
	state->TunerRegs[21].Reg_Val = 0x01 ;

	state->TunerRegs[22].Reg_Num = 37 ;
	state->TunerRegs[22].Reg_Val = 0x00 ;

	state->TunerRegs[23].Reg_Num = 41 ;
	state->TunerRegs[23].Reg_Val = 0x00 ;

	state->TunerRegs[24].Reg_Num = 42 ;
	state->TunerRegs[24].Reg_Val = 0xF8 ;

	state->TunerRegs[25].Reg_Num = 43 ;
	state->TunerRegs[25].Reg_Val = 0x43 ;

	state->TunerRegs[26].Reg_Num = 44 ;
	state->TunerRegs[26].Reg_Val = 0x20 ;

	state->TunerRegs[27].Reg_Num = 45 ;
	state->TunerRegs[27].Reg_Val = 0x80 ;

	state->TunerRegs[28].Reg_Num = 46 ;
	state->TunerRegs[28].Reg_Val = 0x88 ;

	state->TunerRegs[29].Reg_Num = 47 ;
	state->TunerRegs[29].Reg_Val = 0x86 ;

	state->TunerRegs[30].Reg_Num = 48 ;
	state->TunerRegs[30].Reg_Val = 0x00 ;

	state->TunerRegs[31].Reg_Num = 49 ;
	state->TunerRegs[31].Reg_Val = 0x00 ;

	state->TunerRegs[32].Reg_Num = 53 ;
	state->TunerRegs[32].Reg_Val = 0x94 ;

	state->TunerRegs[33].Reg_Num = 54 ;
	state->TunerRegs[33].Reg_Val = 0xFA ;

	state->TunerRegs[34].Reg_Num = 55 ;
	state->TunerRegs[34].Reg_Val = 0x92 ;

	state->TunerRegs[35].Reg_Num = 56 ;
	state->TunerRegs[35].Reg_Val = 0x80 ;

	state->TunerRegs[36].Reg_Num = 57 ;
	state->TunerRegs[36].Reg_Val = 0x41 ;

	state->TunerRegs[37].Reg_Num = 58 ;
	state->TunerRegs[37].Reg_Val = 0xDB ;

	state->TunerRegs[38].Reg_Num = 59 ;
	state->TunerRegs[38].Reg_Val = 0x00 ;

	state->TunerRegs[39].Reg_Num = 60 ;
	state->TunerRegs[39].Reg_Val = 0x00 ;

	state->TunerRegs[40].Reg_Num = 61 ;
	state->TunerRegs[40].Reg_Val = 0x00 ;

	state->TunerRegs[41].Reg_Num = 62 ;
	state->TunerRegs[41].Reg_Val = 0x00 ;

	state->TunerRegs[42].Reg_Num = 65 ;
	state->TunerRegs[42].Reg_Val = 0xF8 ;

	state->TunerRegs[43].Reg_Num = 66 ;
	state->TunerRegs[43].Reg_Val = 0xE4 ;

	state->TunerRegs[44].Reg_Num = 67 ;
	state->TunerRegs[44].Reg_Val = 0x90 ;

	state->TunerRegs[45].Reg_Num = 68 ;
	state->TunerRegs[45].Reg_Val = 0xC0 ;

	state->TunerRegs[46].Reg_Num = 69 ;
	state->TunerRegs[46].Reg_Val = 0x01 ;

	state->TunerRegs[47].Reg_Num = 70 ;
	state->TunerRegs[47].Reg_Val = 0x50 ;

	state->TunerRegs[48].Reg_Num = 71 ;
	state->TunerRegs[48].Reg_Val = 0x06 ;

	state->TunerRegs[49].Reg_Num = 72 ;
	state->TunerRegs[49].Reg_Val = 0x00 ;

	state->TunerRegs[50].Reg_Num = 73 ;
	state->TunerRegs[50].Reg_Val = 0x20 ;

	state->TunerRegs[51].Reg_Num = 76 ;
	state->TunerRegs[51].Reg_Val = 0xBB ;

	state->TunerRegs[52].Reg_Num = 77 ;
	state->TunerRegs[52].Reg_Val = 0x13 ;

	state->TunerRegs[53].Reg_Num = 81 ;
	state->TunerRegs[53].Reg_Val = 0x04 ;

	state->TunerRegs[54].Reg_Num = 82 ;
	state->TunerRegs[54].Reg_Val = 0x75 ;

	state->TunerRegs[55].Reg_Num = 83 ;
	state->TunerRegs[55].Reg_Val = 0x00 ;

	state->TunerRegs[56].Reg_Num = 84 ;
	state->TunerRegs[56].Reg_Val = 0x00 ;

	state->TunerRegs[57].Reg_Num = 85 ;
	state->TunerRegs[57].Reg_Val = 0x00 ;

	state->TunerRegs[58].Reg_Num = 91 ;
	state->TunerRegs[58].Reg_Val = 0x70 ;

	state->TunerRegs[59].Reg_Num = 92 ;
	state->TunerRegs[59].Reg_Val = 0x00 ;

	state->TunerRegs[60].Reg_Num = 93 ;
	state->TunerRegs[60].Reg_Val = 0x00 ;

	state->TunerRegs[61].Reg_Num = 94 ;
	state->TunerRegs[61].Reg_Val = 0x00 ;

	state->TunerRegs[62].Reg_Num = 95 ;
	state->TunerRegs[62].Reg_Val = 0x0C ;

	state->TunerRegs[63].Reg_Num = 96 ;
	state->TunerRegs[63].Reg_Val = 0x00 ;

	state->TunerRegs[64].Reg_Num = 97 ;
	state->TunerRegs[64].Reg_Val = 0x00 ;

	state->TunerRegs[65].Reg_Num = 98 ;
	state->TunerRegs[65].Reg_Val = 0xE2 ;

	state->TunerRegs[66].Reg_Num = 99 ;
	state->TunerRegs[66].Reg_Val = 0x00 ;

	state->TunerRegs[67].Reg_Num = 100 ;
	state->TunerRegs[67].Reg_Val = 0x00 ;

	state->TunerRegs[68].Reg_Num = 101 ;
	state->TunerRegs[68].Reg_Val = 0x12 ;

	state->TunerRegs[69].Reg_Num = 102 ;
	state->TunerRegs[69].Reg_Val = 0x80 ;

	state->TunerRegs[70].Reg_Num = 103 ;
	state->TunerRegs[70].Reg_Val = 0x32 ;

	state->TunerRegs[71].Reg_Num = 104 ;
	state->TunerRegs[71].Reg_Val = 0xB4 ;

	state->TunerRegs[72].Reg_Num = 105 ;
	state->TunerRegs[72].Reg_Val = 0x60 ;

	state->TunerRegs[73].Reg_Num = 106 ;
	state->TunerRegs[73].Reg_Val = 0x83 ;

	state->TunerRegs[74].Reg_Num = 107 ;
	state->TunerRegs[74].Reg_Val = 0x84 ;

	state->TunerRegs[75].Reg_Num = 108 ;
	state->TunerRegs[75].Reg_Val = 0x9C ;

	state->TunerRegs[76].Reg_Num = 109 ;
	state->TunerRegs[76].Reg_Val = 0x02 ;

	state->TunerRegs[77].Reg_Num = 110 ;
	state->TunerRegs[77].Reg_Val = 0x81 ;

	state->TunerRegs[78].Reg_Num = 111 ;
	state->TunerRegs[78].Reg_Val = 0xC0 ;

	state->TunerRegs[79].Reg_Num = 112 ;
	state->TunerRegs[79].Reg_Val = 0x10 ;

	state->TunerRegs[80].Reg_Num = 131 ;
	state->TunerRegs[80].Reg_Val = 0x8A ;

	state->TunerRegs[81].Reg_Num = 132 ;
	state->TunerRegs[81].Reg_Val = 0x10 ;

	state->TunerRegs[82].Reg_Num = 133 ;
	state->TunerRegs[82].Reg_Val = 0x24 ;

	state->TunerRegs[83].Reg_Num = 134 ;
	state->TunerRegs[83].Reg_Val = 0x00 ;

	state->TunerRegs[84].Reg_Num = 135 ;
	state->TunerRegs[84].Reg_Val = 0x00 ;

	state->TunerRegs[85].Reg_Num = 136 ;
	state->TunerRegs[85].Reg_Val = 0x7E ;

	state->TunerRegs[86].Reg_Num = 137 ;
	state->TunerRegs[86].Reg_Val = 0x40 ;

	state->TunerRegs[87].Reg_Num = 138 ;
	state->TunerRegs[87].Reg_Val = 0x38 ;

	state->TunerRegs[88].Reg_Num = 146 ;
	state->TunerRegs[88].Reg_Val = 0xF6 ;

	state->TunerRegs[89].Reg_Num = 147 ;
	state->TunerRegs[89].Reg_Val = 0x1A ;

	state->TunerRegs[90].Reg_Num = 148 ;
	state->TunerRegs[90].Reg_Val = 0x62 ;

	state->TunerRegs[91].Reg_Num = 149 ;
	state->TunerRegs[91].Reg_Val = 0x33 ;

	state->TunerRegs[92].Reg_Num = 150 ;
	state->TunerRegs[92].Reg_Val = 0x80 ;

	state->TunerRegs[93].Reg_Num = 156 ;
	state->TunerRegs[93].Reg_Val = 0x56 ;

	state->TunerRegs[94].Reg_Num = 157 ;
	state->TunerRegs[94].Reg_Val = 0x17 ;

	state->TunerRegs[95].Reg_Num = 158 ;
	state->TunerRegs[95].Reg_Val = 0xA9 ;

	state->TunerRegs[96].Reg_Num = 159 ;
	state->TunerRegs[96].Reg_Val = 0x00 ;

	state->TunerRegs[97].Reg_Num = 160 ;
	state->TunerRegs[97].Reg_Val = 0x00 ;

	state->TunerRegs[98].Reg_Num = 161 ;
	state->TunerRegs[98].Reg_Val = 0x00 ;

	state->TunerRegs[99].Reg_Num = 162 ;
	state->TunerRegs[99].Reg_Val = 0x40 ;

	state->TunerRegs[100].Reg_Num = 166 ;
	state->TunerRegs[100].Reg_Val = 0xAE ;

	state->TunerRegs[101].Reg_Num = 167 ;
	state->TunerRegs[101].Reg_Val = 0x1B ;

	state->TunerRegs[102].Reg_Num = 168 ;
	state->TunerRegs[102].Reg_Val = 0xF2 ;

	state->TunerRegs[103].Reg_Num = 195 ;
	state->TunerRegs[103].Reg_Val = 0x00 ;

	return 0 ;
}