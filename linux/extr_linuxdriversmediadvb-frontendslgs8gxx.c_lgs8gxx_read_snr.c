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
typedef  int u8 ;
typedef  int u16 ;
struct lgs8gxx_state {TYPE_1__* config; } ;
struct dvb_frontend {struct lgs8gxx_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ prod; } ;

/* Variables and functions */
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  lgs8gxx_read_reg (struct lgs8gxx_state*,int,int*) ; 

__attribute__((used)) static int lgs8gxx_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct lgs8gxx_state *priv = fe->demodulator_priv;
	u8 t;
	*snr = 0;

	if (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		lgs8gxx_read_reg(priv, 0x34, &t);
	else
		lgs8gxx_read_reg(priv, 0x95, &t);
	dprintk("AVG Noise=0x%02X\n", t);
	*snr = 256 - t;
	*snr <<= 8;
	dprintk("snr=0x%x\n", *snr);

	return 0;
}