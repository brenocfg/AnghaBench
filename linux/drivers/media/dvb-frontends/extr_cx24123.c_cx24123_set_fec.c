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
struct cx24123_state {int dummy; } ;
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FEC_1_2 135 
#define  FEC_2_3 134 
#define  FEC_3_4 133 
#define  FEC_4_5 132 
#define  FEC_5_6 131 
#define  FEC_6_7 130 
#define  FEC_7_8 129 
#define  FEC_AUTO 128 
 int FEC_NONE ; 
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  cx24123_writereg (struct cx24123_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int cx24123_set_fec(struct cx24123_state *state, enum fe_code_rate fec)
{
	u8 nom_reg = cx24123_readreg(state, 0x0e) & ~0x07;

	if (((int)fec < FEC_NONE) || (fec > FEC_AUTO))
		fec = FEC_AUTO;

	/* Set the soft decision threshold */
	if (fec == FEC_1_2)
		cx24123_writereg(state, 0x43,
			cx24123_readreg(state, 0x43) | 0x01);
	else
		cx24123_writereg(state, 0x43,
			cx24123_readreg(state, 0x43) & ~0x01);

	switch (fec) {
	case FEC_1_2:
		dprintk("set FEC to 1/2\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x01);
		cx24123_writereg(state, 0x0f, 0x02);
		break;
	case FEC_2_3:
		dprintk("set FEC to 2/3\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x02);
		cx24123_writereg(state, 0x0f, 0x04);
		break;
	case FEC_3_4:
		dprintk("set FEC to 3/4\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x03);
		cx24123_writereg(state, 0x0f, 0x08);
		break;
	case FEC_4_5:
		dprintk("set FEC to 4/5\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x04);
		cx24123_writereg(state, 0x0f, 0x10);
		break;
	case FEC_5_6:
		dprintk("set FEC to 5/6\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x05);
		cx24123_writereg(state, 0x0f, 0x20);
		break;
	case FEC_6_7:
		dprintk("set FEC to 6/7\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x06);
		cx24123_writereg(state, 0x0f, 0x40);
		break;
	case FEC_7_8:
		dprintk("set FEC to 7/8\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x07);
		cx24123_writereg(state, 0x0f, 0x80);
		break;
	case FEC_AUTO:
		dprintk("set FEC to auto\n");
		cx24123_writereg(state, 0x0f, 0xfe);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}