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
struct m88ds3103_dev {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct dvb_frontend {struct m88ds3103_dev* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 

__attribute__((used)) static void m88ds3103_release(struct dvb_frontend *fe)
{
	struct m88ds3103_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;

	i2c_unregister_device(client);
}