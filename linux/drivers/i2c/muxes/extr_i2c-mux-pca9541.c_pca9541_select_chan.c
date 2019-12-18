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
struct pca9541 {int select_timeout; scalar_t__ arb_timeout; struct i2c_client* client; } ;
struct i2c_mux_core {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 unsigned long ARB2_TIMEOUT ; 
 scalar_t__ ARB_TIMEOUT ; 
 int ETIMEDOUT ; 
 int SELECT_DELAY_SHORT ; 
 struct pca9541* i2c_mux_priv (struct i2c_mux_core*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pca9541_arbitrate (struct i2c_client*) ; 
 scalar_t__ time_is_after_eq_jiffies (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pca9541_select_chan(struct i2c_mux_core *muxc, u32 chan)
{
	struct pca9541 *data = i2c_mux_priv(muxc);
	struct i2c_client *client = data->client;
	int ret;
	unsigned long timeout = jiffies + ARB2_TIMEOUT;
		/* give up after this time */

	data->arb_timeout = jiffies + ARB_TIMEOUT;
		/* force bus ownership after this time */

	do {
		ret = pca9541_arbitrate(client);
		if (ret)
			return ret < 0 ? ret : 0;

		if (data->select_timeout == SELECT_DELAY_SHORT)
			udelay(data->select_timeout);
		else
			msleep(data->select_timeout / 1000);
	} while (time_is_after_eq_jiffies(timeout));

	return -ETIMEDOUT;
}