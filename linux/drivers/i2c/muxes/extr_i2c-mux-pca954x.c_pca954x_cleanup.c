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
struct pca954x {scalar_t__ irq; TYPE_1__* chip; struct i2c_client* client; } ;
struct i2c_mux_core {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int nchans; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_idle_state ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (struct i2c_mux_core*) ; 
 struct pca954x* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  irq_domain_remove (scalar_t__) ; 
 int irq_find_mapping (scalar_t__,int) ; 

__attribute__((used)) static void pca954x_cleanup(struct i2c_mux_core *muxc)
{
	struct pca954x *data = i2c_mux_priv(muxc);
	struct i2c_client *client = data->client;
	int c, irq;

	device_remove_file(&client->dev, &dev_attr_idle_state);

	if (data->irq) {
		for (c = 0; c < data->chip->nchans; c++) {
			irq = irq_find_mapping(data->irq, c);
			irq_dispose_mapping(irq);
		}
		irq_domain_remove(data->irq);
	}
	i2c_mux_del_adapters(muxc);
}