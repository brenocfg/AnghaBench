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
struct microtune_priv {int dummy; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt2032_spurcheck (struct dvb_frontend*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ optimize_vco ; 
 int /*<<< orphan*/  tuner_dbg (char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tuner_info (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int mt2032_compute_freq(struct dvb_frontend *fe,
			       unsigned int rfin,
			       unsigned int if1, unsigned int if2,
			       unsigned int spectrum_from,
			       unsigned int spectrum_to,
			       unsigned char *buf,
			       int *ret_sel,
			       unsigned int xogc) //all in Hz
{
	struct microtune_priv *priv = fe->tuner_priv;
	unsigned int fref,lo1,lo1n,lo1a,s,sel,lo1freq, desired_lo1,
		desired_lo2,lo2,lo2n,lo2a,lo2num,lo2freq;

	fref= 5250 *1000; //5.25MHz
	desired_lo1=rfin+if1;

	lo1=(2*(desired_lo1/1000)+(fref/1000)) / (2*fref/1000);
	lo1n=lo1/8;
	lo1a=lo1-(lo1n*8);

	s=rfin/1000/1000+1090;

	if(optimize_vco) {
		if(s>1890) sel=0;
		else if(s>1720) sel=1;
		else if(s>1530) sel=2;
		else if(s>1370) sel=3;
		else sel=4; // >1090
	}
	else {
		if(s>1790) sel=0; // <1958
		else if(s>1617) sel=1;
		else if(s>1449) sel=2;
		else if(s>1291) sel=3;
		else sel=4; // >1090
	}
	*ret_sel=sel;

	lo1freq=(lo1a+8*lo1n)*fref;

	tuner_dbg("mt2032: rfin=%d lo1=%d lo1n=%d lo1a=%d sel=%d, lo1freq=%d\n",
		  rfin,lo1,lo1n,lo1a,sel,lo1freq);

	desired_lo2=lo1freq-rfin-if2;
	lo2=(desired_lo2)/fref;
	lo2n=lo2/8;
	lo2a=lo2-(lo2n*8);
	lo2num=((desired_lo2/1000)%(fref/1000))* 3780/(fref/1000); //scale to fit in 32bit arith
	lo2freq=(lo2a+8*lo2n)*fref + lo2num*(fref/1000)/3780*1000;

	tuner_dbg("mt2032: rfin=%d lo2=%d lo2n=%d lo2a=%d num=%d lo2freq=%d\n",
		  rfin,lo2,lo2n,lo2a,lo2num,lo2freq);

	if (lo1a > 7 || lo1n < 17 || lo1n > 48 || lo2a > 7 || lo2n < 17 ||
			lo2n > 30) {
		tuner_info("mt2032: frequency parameters out of range: %d %d %d %d\n",
			   lo1a, lo1n, lo2a,lo2n);
		return(-1);
	}

	mt2032_spurcheck(fe, lo1freq, desired_lo2,  spectrum_from, spectrum_to);
	// should recalculate lo1 (one step up/down)

	// set up MT2032 register map for transfer over i2c
	buf[0]=lo1n-1;
	buf[1]=lo1a | (sel<<4);
	buf[2]=0x86; // LOGC
	buf[3]=0x0f; //reserved
	buf[4]=0x1f;
	buf[5]=(lo2n-1) | (lo2a<<5);
	if(rfin >400*1000*1000)
		buf[6]=0xe4;
	else
		buf[6]=0xf4; // set PKEN per rev 1.2
	buf[7]=8+xogc;
	buf[8]=0xc3; //reserved
	buf[9]=0x4e; //reserved
	buf[10]=0xec; //reserved
	buf[11]=(lo2num&0xff);
	buf[12]=(lo2num>>8) |0x80; // Lo2RST

	return 0;
}