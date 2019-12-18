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
struct i2c_client {int dummy; } ;
struct dvb_pll_priv {int /*<<< orphan*/  nr; } ;
struct dvb_frontend {struct dvb_pll_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_pll_release (struct dvb_frontend*) ; 
 struct dvb_frontend* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_ida ; 

__attribute__((used)) static int dvb_pll_remove(struct i2c_client *client)
{
	struct dvb_frontend *fe = i2c_get_clientdata(client);
	struct dvb_pll_priv *priv = fe->tuner_priv;

	ida_simple_remove(&pll_ida, priv->nr);
	dvb_pll_release(fe);
	return 0;
}