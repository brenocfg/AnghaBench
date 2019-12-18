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
typedef  scalar_t__ u32 ;
struct tua9001_dev {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct tua9001_dev* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int tua9001_get_if_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct tua9001_dev *dev = fe->tuner_priv;
	struct i2c_client *client = dev->client;

	dev_dbg(&client->dev, "\n");

	*frequency = 0; /* Zero-IF */
	return 0;
}