#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * class; int /*<<< orphan*/ * type; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct rc_dev {int driver_type; TYPE_4__ dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  keylock; TYPE_1__ rc_map; int /*<<< orphan*/  timer_repeat; int /*<<< orphan*/  timer_keyup; int /*<<< orphan*/  timeout; TYPE_2__* input_dev; } ;
typedef  enum rc_driver_type { ____Placeholder_rc_driver_type } rc_driver_type ;
struct TYPE_6__ {int /*<<< orphan*/  setkeycode; int /*<<< orphan*/  getkeycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IR_DEFAULT_TIMEOUT ; 
 int RC_DRIVER_IR_RAW_TX ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_4__*) ; 
 TYPE_2__* input_allocate_device () ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct rc_dev*) ; 
 int /*<<< orphan*/  ir_getkeycode ; 
 int /*<<< orphan*/  ir_setkeycode ; 
 int /*<<< orphan*/  ir_timer_keyup ; 
 int /*<<< orphan*/  ir_timer_repeat ; 
 int /*<<< orphan*/  kfree (struct rc_dev*) ; 
 struct rc_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_class ; 
 int /*<<< orphan*/  rc_dev_type ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rc_dev *rc_allocate_device(enum rc_driver_type type)
{
	struct rc_dev *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	if (type != RC_DRIVER_IR_RAW_TX) {
		dev->input_dev = input_allocate_device();
		if (!dev->input_dev) {
			kfree(dev);
			return NULL;
		}

		dev->input_dev->getkeycode = ir_getkeycode;
		dev->input_dev->setkeycode = ir_setkeycode;
		input_set_drvdata(dev->input_dev, dev);

		dev->timeout = IR_DEFAULT_TIMEOUT;
		timer_setup(&dev->timer_keyup, ir_timer_keyup, 0);
		timer_setup(&dev->timer_repeat, ir_timer_repeat, 0);

		spin_lock_init(&dev->rc_map.lock);
		spin_lock_init(&dev->keylock);
	}
	mutex_init(&dev->lock);

	dev->dev.type = &rc_dev_type;
	dev->dev.class = &rc_class;
	device_initialize(&dev->dev);

	dev->driver_type = type;

	__module_get(THIS_MODULE);
	return dev;
}