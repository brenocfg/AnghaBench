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
struct tda827x_priv {int /*<<< orphan*/  i2c_addr; } ;
struct i2c_msg {unsigned char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_frontend {struct tda827x_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tuner_transfer (struct dvb_frontend*,struct i2c_msg*,int) ; 

__attribute__((used)) static void tda827xo_agcf(struct dvb_frontend *fe)
{
	struct tda827x_priv *priv = fe->tuner_priv;
	unsigned char data[] = { 0x80, 0x0c };
	struct i2c_msg msg = { .addr = priv->i2c_addr, .flags = 0,
			       .buf = data, .len = 2};

	tuner_transfer(fe, &msg, 1);
}