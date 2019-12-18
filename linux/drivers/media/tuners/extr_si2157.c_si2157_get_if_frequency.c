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
struct si2157_dev {int /*<<< orphan*/  if_frequency; } ;
struct i2c_client {int dummy; } ;
struct dvb_frontend {struct i2c_client* tuner_priv; } ;

/* Variables and functions */
 struct si2157_dev* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int si2157_get_if_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct i2c_client *client = fe->tuner_priv;
	struct si2157_dev *dev = i2c_get_clientdata(client);

	*frequency = dev->if_frequency;
	return 0;
}