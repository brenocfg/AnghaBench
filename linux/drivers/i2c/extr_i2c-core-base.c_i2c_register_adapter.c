#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  parent; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct i2c_adapter {scalar_t__ timeout; scalar_t__ nr; int /*<<< orphan*/  dev_released; TYPE_1__ dev; int /*<<< orphan*/ * name; int /*<<< orphan*/  userspace_clients; int /*<<< orphan*/  userspace_clients_lock; int /*<<< orphan*/  mux_lock; int /*<<< orphan*/  bus_lock; scalar_t__ locked_flags; int /*<<< orphan*/ * lock_ops; int /*<<< orphan*/  algo; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN (int,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ __i2c_first_dynamic_bus_num ; 
 int /*<<< orphan*/  __process_new_adapter ; 
 int /*<<< orphan*/  bus_for_each_drv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int class_compat_create_link (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_lock ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_acpi_install_space_handler (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_acpi_register_devices (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_adapter_compat_class ; 
 int /*<<< orphan*/  i2c_adapter_idr ; 
 int /*<<< orphan*/  i2c_adapter_lock_ops ; 
 int /*<<< orphan*/  i2c_adapter_type ; 
 int /*<<< orphan*/  i2c_bus_type ; 
 int /*<<< orphan*/  i2c_init_recovery (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_scan_static_board_info (struct i2c_adapter*) ; 
 int i2c_setup_host_notify_irq_domain (struct i2c_adapter*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_registered ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_i2c_register_devices (struct i2c_adapter*) ; 
 int of_i2c_setup_smbus_alert (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  rt_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_register_adapter(struct i2c_adapter *adap)
{
	int res = -EINVAL;

	/* Can't register until after driver model init */
	if (WARN_ON(!is_registered)) {
		res = -EAGAIN;
		goto out_list;
	}

	/* Sanity checks */
	if (WARN(!adap->name[0], "i2c adapter has no name"))
		goto out_list;

	if (!adap->algo) {
		pr_err("adapter '%s': no algo supplied!\n", adap->name);
		goto out_list;
	}

	if (!adap->lock_ops)
		adap->lock_ops = &i2c_adapter_lock_ops;

	adap->locked_flags = 0;
	rt_mutex_init(&adap->bus_lock);
	rt_mutex_init(&adap->mux_lock);
	mutex_init(&adap->userspace_clients_lock);
	INIT_LIST_HEAD(&adap->userspace_clients);

	/* Set default timeout to 1 second if not already set */
	if (adap->timeout == 0)
		adap->timeout = HZ;

	/* register soft irqs for Host Notify */
	res = i2c_setup_host_notify_irq_domain(adap);
	if (res) {
		pr_err("adapter '%s': can't create Host Notify IRQs (%d)\n",
		       adap->name, res);
		goto out_list;
	}

	dev_set_name(&adap->dev, "i2c-%d", adap->nr);
	adap->dev.bus = &i2c_bus_type;
	adap->dev.type = &i2c_adapter_type;
	res = device_register(&adap->dev);
	if (res) {
		pr_err("adapter '%s': can't register device (%d)\n", adap->name, res);
		goto out_list;
	}

	res = of_i2c_setup_smbus_alert(adap);
	if (res)
		goto out_reg;

	dev_dbg(&adap->dev, "adapter [%s] registered\n", adap->name);

	pm_runtime_no_callbacks(&adap->dev);
	pm_suspend_ignore_children(&adap->dev, true);
	pm_runtime_enable(&adap->dev);

#ifdef CONFIG_I2C_COMPAT
	res = class_compat_create_link(i2c_adapter_compat_class, &adap->dev,
				       adap->dev.parent);
	if (res)
		dev_warn(&adap->dev,
			 "Failed to create compatibility class link\n");
#endif

	i2c_init_recovery(adap);

	/* create pre-declared device nodes */
	of_i2c_register_devices(adap);
	i2c_acpi_register_devices(adap);
	i2c_acpi_install_space_handler(adap);

	if (adap->nr < __i2c_first_dynamic_bus_num)
		i2c_scan_static_board_info(adap);

	/* Notify drivers */
	mutex_lock(&core_lock);
	bus_for_each_drv(&i2c_bus_type, NULL, adap, __process_new_adapter);
	mutex_unlock(&core_lock);

	return 0;

out_reg:
	init_completion(&adap->dev_released);
	device_unregister(&adap->dev);
	wait_for_completion(&adap->dev_released);
out_list:
	mutex_lock(&core_lock);
	idr_remove(&i2c_adapter_idr, adap->nr);
	mutex_unlock(&core_lock);
	return res;
}