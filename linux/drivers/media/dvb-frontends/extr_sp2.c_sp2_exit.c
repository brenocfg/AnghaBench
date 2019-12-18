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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct sp2 {TYPE_1__ ca; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dvb_ca_en50221_release (TYPE_1__*) ; 
 struct sp2* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int sp2_exit(struct i2c_client *client)
{
	struct sp2 *s;

	dev_dbg(&client->dev, "\n");

	if (!client)
		return 0;

	s = i2c_get_clientdata(client);
	if (!s)
		return 0;

	if (!s->ca.data)
		return 0;

	dvb_ca_en50221_release(&s->ca);

	return 0;
}