#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct channel_info {TYPE_3__* i2c_client; int /*<<< orphan*/  i2c_adapter; scalar_t__ frontend; } ;
struct c8sectpfei {int tsin_count; struct channel_info** channel_data; } ;
struct c8sectpfe {int dummy; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  c8sectpfe_delete (struct c8sectpfe*) ; 
 int /*<<< orphan*/  dvb_frontend_detach (scalar_t__) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unregister_device (TYPE_3__*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void c8sectpfe_tuner_unregister_frontend(struct c8sectpfe *c8sectpfe,
					struct c8sectpfei *fei)
{
	int n;
	struct channel_info *tsin;

	for (n = 0; n < fei->tsin_count; n++) {

		tsin = fei->channel_data[n];

		if (tsin) {
			if (tsin->frontend) {
				dvb_unregister_frontend(tsin->frontend);
				dvb_frontend_detach(tsin->frontend);
			}

			i2c_put_adapter(tsin->i2c_adapter);

			if (tsin->i2c_client) {
				module_put(tsin->i2c_client->dev.driver->owner);
				i2c_unregister_device(tsin->i2c_client);
			}
		}
	}

	c8sectpfe_delete(c8sectpfe);
}