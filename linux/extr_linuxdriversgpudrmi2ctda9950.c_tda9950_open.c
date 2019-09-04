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
struct tda9950_priv {int /*<<< orphan*/  adap; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_ON ; 
 int /*<<< orphan*/  CCR_RESET ; 
 int /*<<< orphan*/  CEC_LOG_ADDR_INVALID ; 
 int /*<<< orphan*/  REG_CCR ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tda9950_cec_adap_log_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tda9950_glue_open (struct tda9950_priv*) ; 
 int /*<<< orphan*/  tda9950_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda9950_open(struct tda9950_priv *priv)
{
	struct i2c_client *client = priv->client;
	int ret;

	ret = tda9950_glue_open(priv);
	if (ret)
		return ret;

	/* Reset the TDA9950, and wait 250ms for it to recover */
	tda9950_write(client, REG_CCR, CCR_RESET);
	msleep(250);

	tda9950_cec_adap_log_addr(priv->adap, CEC_LOG_ADDR_INVALID);

	/* Start the command processor */
	tda9950_write(client, REG_CCR, CCR_ON);

	return 0;
}