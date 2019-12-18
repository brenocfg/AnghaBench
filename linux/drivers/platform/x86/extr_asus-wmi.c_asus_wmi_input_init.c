#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct asus_wmi {TYPE_5__* inputdev; TYPE_4__* driver; TYPE_3__* platform_device; } ;
struct TYPE_10__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_13__ {int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int /*<<< orphan*/  keymap; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  input_name; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_REP ; 
 TYPE_5__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_5__*) ; 
 int input_register_device (TYPE_5__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sparse_keymap_setup (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_wmi_input_init(struct asus_wmi *asus)
{
	int err;

	asus->inputdev = input_allocate_device();
	if (!asus->inputdev)
		return -ENOMEM;

	asus->inputdev->name = asus->driver->input_name;
	asus->inputdev->phys = asus->driver->input_phys;
	asus->inputdev->id.bustype = BUS_HOST;
	asus->inputdev->dev.parent = &asus->platform_device->dev;
	set_bit(EV_REP, asus->inputdev->evbit);

	err = sparse_keymap_setup(asus->inputdev, asus->driver->keymap, NULL);
	if (err)
		goto err_free_dev;

	err = input_register_device(asus->inputdev);
	if (err)
		goto err_free_dev;

	return 0;

err_free_dev:
	input_free_device(asus->inputdev);
	return err;
}