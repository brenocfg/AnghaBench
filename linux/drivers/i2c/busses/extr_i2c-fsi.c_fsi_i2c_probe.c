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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {struct device* parent; struct device_node* of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; struct fsi_i2c_port* algo_data; int /*<<< orphan*/ * bus_recovery_info; int /*<<< orphan*/ * algo; TYPE_1__ dev; int /*<<< orphan*/  owner; } ;
struct fsi_i2c_port {int /*<<< orphan*/  list; TYPE_2__ adapter; scalar_t__ port; struct fsi_i2c_master* master; } ;
struct fsi_i2c_master {int /*<<< orphan*/  ports; int /*<<< orphan*/  fsi; int /*<<< orphan*/  lock; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FSI_STAT ; 
 int /*<<< orphan*/  I2C_STAT_MAX_PORT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct fsi_i2c_master*) ; 
 struct fsi_i2c_master* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_i2c_algorithm ; 
 int /*<<< orphan*/  fsi_i2c_bus_recovery_info ; 
 int fsi_i2c_dev_init (struct fsi_i2c_master*) ; 
 struct device_node* fsi_i2c_find_port_of_node (int /*<<< orphan*/ ,scalar_t__) ; 
 int fsi_i2c_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct fsi_i2c_port*) ; 
 struct fsi_i2c_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  to_fsi_dev (struct device*) ; 

__attribute__((used)) static int fsi_i2c_probe(struct device *dev)
{
	struct fsi_i2c_master *i2c;
	struct fsi_i2c_port *port;
	struct device_node *np;
	u32 port_no, ports, stat;
	int rc;

	i2c = devm_kzalloc(dev, sizeof(*i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	mutex_init(&i2c->lock);
	i2c->fsi = to_fsi_dev(dev);
	INIT_LIST_HEAD(&i2c->ports);

	rc = fsi_i2c_dev_init(i2c);
	if (rc)
		return rc;

	rc = fsi_i2c_read_reg(i2c->fsi, I2C_FSI_STAT, &stat);
	if (rc)
		return rc;

	ports = FIELD_GET(I2C_STAT_MAX_PORT, stat) + 1;
	dev_dbg(dev, "I2C master has %d ports\n", ports);

	for (port_no = 0; port_no < ports; port_no++) {
		np = fsi_i2c_find_port_of_node(dev->of_node, port_no);
		if (np && !of_device_is_available(np))
			continue;

		port = kzalloc(sizeof(*port), GFP_KERNEL);
		if (!port) {
			of_node_put(np);
			break;
		}

		port->master = i2c;
		port->port = port_no;

		port->adapter.owner = THIS_MODULE;
		port->adapter.dev.of_node = np;
		port->adapter.dev.parent = dev;
		port->adapter.algo = &fsi_i2c_algorithm;
		port->adapter.bus_recovery_info = &fsi_i2c_bus_recovery_info;
		port->adapter.algo_data = port;

		snprintf(port->adapter.name, sizeof(port->adapter.name),
			 "i2c_bus-%u", port_no);

		rc = i2c_add_adapter(&port->adapter);
		if (rc < 0) {
			dev_err(dev, "Failed to register adapter: %d\n", rc);
			kfree(port);
			continue;
		}

		list_add(&port->list, &i2c->ports);
	}

	dev_set_drvdata(dev, i2c);

	return 0;
}