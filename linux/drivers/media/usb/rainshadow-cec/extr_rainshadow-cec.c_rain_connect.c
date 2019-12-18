#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct serio_driver {int dummy; } ;
struct serio {int /*<<< orphan*/  dev; } ;
struct rain {TYPE_2__* adap; int /*<<< orphan*/ * dev; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  work; struct serio* serio; } ;
struct cec_log_addrs {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_1__ devnode; } ;

/* Variables and functions */
 int CEC_CAP_DEFAULTS ; 
 int CEC_CAP_MONITOR_ALL ; 
 int CEC_CAP_PHYS_ADDR ; 
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (TYPE_2__*) ; 
 TYPE_2__* cec_allocate_adapter (int /*<<< orphan*/ *,struct rain*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cec_delete_adapter (TYPE_2__*) ; 
 int cec_register_adapter (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rain*) ; 
 struct rain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rain_cec_adap_ops ; 
 int /*<<< orphan*/  rain_irq_work_handler ; 
 int rain_setup (struct rain*,struct serio*,struct cec_log_addrs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct rain*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rain_connect(struct serio *serio, struct serio_driver *drv)
{
	u32 caps = CEC_CAP_DEFAULTS | CEC_CAP_PHYS_ADDR | CEC_CAP_MONITOR_ALL;
	struct rain *rain;
	int err = -ENOMEM;
	struct cec_log_addrs log_addrs = {};
	u16 pa = CEC_PHYS_ADDR_INVALID;

	rain = kzalloc(sizeof(*rain), GFP_KERNEL);

	if (!rain)
		return -ENOMEM;

	rain->serio = serio;
	rain->adap = cec_allocate_adapter(&rain_cec_adap_ops, rain,
					  dev_name(&serio->dev), caps, 1);
	err = PTR_ERR_OR_ZERO(rain->adap);
	if (err < 0)
		goto free_device;

	rain->dev = &serio->dev;
	serio_set_drvdata(serio, rain);
	INIT_WORK(&rain->work, rain_irq_work_handler);
	mutex_init(&rain->write_lock);
	spin_lock_init(&rain->buf_lock);

	err = serio_open(serio, drv);
	if (err)
		goto delete_adap;

	err = rain_setup(rain, serio, &log_addrs, &pa);
	if (err)
		goto close_serio;

	err = cec_register_adapter(rain->adap, &serio->dev);
	if (err < 0)
		goto close_serio;

	rain->dev = &rain->adap->devnode.dev;
	return 0;

close_serio:
	serio_close(serio);
delete_adap:
	cec_delete_adapter(rain->adap);
	serio_set_drvdata(serio, NULL);
free_device:
	kfree(rain);
	return err;
}