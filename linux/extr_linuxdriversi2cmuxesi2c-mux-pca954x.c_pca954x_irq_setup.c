#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pca954x {int /*<<< orphan*/  irq; TYPE_1__* chip; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct i2c_mux_core {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {scalar_t__ irq; TYPE_2__ dev; } ;
struct TYPE_3__ {int nchans; int /*<<< orphan*/  has_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 struct pca954x* i2c_mux_priv (struct i2c_mux_core*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct pca954x*) ; 
 int /*<<< orphan*/  irq_domain_simple_ops ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (int,struct pca954x*) ; 
 int /*<<< orphan*/  pca954x_irq_chip ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca954x_irq_setup(struct i2c_mux_core *muxc)
{
	struct pca954x *data = i2c_mux_priv(muxc);
	struct i2c_client *client = data->client;
	int c, irq;

	if (!data->chip->has_irq || client->irq <= 0)
		return 0;

	raw_spin_lock_init(&data->lock);

	data->irq = irq_domain_add_linear(client->dev.of_node,
					  data->chip->nchans,
					  &irq_domain_simple_ops, data);
	if (!data->irq)
		return -ENODEV;

	for (c = 0; c < data->chip->nchans; c++) {
		irq = irq_create_mapping(data->irq, c);
		if (!irq) {
			dev_err(&client->dev, "failed irq create map\n");
			return -EINVAL;
		}
		irq_set_chip_data(irq, data);
		irq_set_chip_and_handler(irq, &pca954x_irq_chip,
			handle_simple_irq);
	}

	return 0;
}