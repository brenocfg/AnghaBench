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
struct hv_kbd_dev {int /*<<< orphan*/  hv_serio; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct hv_kbd_dev* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hv_kbd_dev*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hv_kbd_remove(struct hv_device *hv_dev)
{
	struct hv_kbd_dev *kbd_dev = hv_get_drvdata(hv_dev);

	serio_unregister_port(kbd_dev->hv_serio);
	vmbus_close(hv_dev->channel);
	kfree(kbd_dev);

	hv_set_drvdata(hv_dev, NULL);

	return 0;
}