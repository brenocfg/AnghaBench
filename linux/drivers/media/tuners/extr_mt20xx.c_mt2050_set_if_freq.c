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
struct microtune_priv {int /*<<< orphan*/  i2c_props; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int debug ; 
 int /*<<< orphan*/  tuner_dbg (char*,int,...) ; 
 int tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_warn (char*,int) ; 

__attribute__((used)) static void mt2050_set_if_freq(struct dvb_frontend *fe,unsigned int freq, unsigned int if2)
{
	struct microtune_priv *priv = fe->tuner_priv;
	unsigned int if1=1218*1000*1000;
	unsigned int f_lo1,f_lo2,lo1,lo2,f_lo1_modulo,f_lo2_modulo,num1,num2,div1a,div1b,div2a,div2b;
	int ret;
	unsigned char buf[6];

	tuner_dbg("mt2050_set_if_freq freq=%d if1=%d if2=%d\n",
		  freq,if1,if2);

	f_lo1=freq+if1;
	f_lo1=(f_lo1/1000000)*1000000;

	f_lo2=f_lo1-freq-if2;
	f_lo2=(f_lo2/50000)*50000;

	lo1=f_lo1/4000000;
	lo2=f_lo2/4000000;

	f_lo1_modulo= f_lo1-(lo1*4000000);
	f_lo2_modulo= f_lo2-(lo2*4000000);

	num1=4*f_lo1_modulo/4000000;
	num2=4096*(f_lo2_modulo/1000)/4000;

	// todo spurchecks

	div1a=(lo1/12)-1;
	div1b=lo1-(div1a+1)*12;

	div2a=(lo2/8)-1;
	div2b=lo2-(div2a+1)*8;

	if (debug > 1) {
		tuner_dbg("lo1 lo2 = %d %d\n", lo1, lo2);
		tuner_dbg("num1 num2 div1a div1b div2a div2b= %x %x %x %x %x %x\n",
			  num1,num2,div1a,div1b,div2a,div2b);
	}

	buf[0]=1;
	buf[1]= 4*div1b + num1;
	if(freq<275*1000*1000) buf[1] = buf[1]|0x80;

	buf[2]=div1a;
	buf[3]=32*div2b + num2/256;
	buf[4]=num2-(num2/256)*256;
	buf[5]=div2a;
	if(num2!=0) buf[5]=buf[5]|0x40;

	if (debug > 1)
		tuner_dbg("bufs is: %*ph\n", 6, buf);

	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,6);
	if (ret!=6)
		tuner_warn("i2c i/o error: rc == %d (should be 6)\n",ret);
}