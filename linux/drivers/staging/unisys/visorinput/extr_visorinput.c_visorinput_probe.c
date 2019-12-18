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
struct visor_device {int /*<<< orphan*/  visorchannel; } ;
typedef  int /*<<< orphan*/  guid_t ;
typedef  enum visorinput_dev_type { ____Placeholder_visorinput_dev_type } visorinput_dev_type ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  devdata_create (struct visor_device*,int) ; 
 scalar_t__ guid_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visor_keyboard_channel_guid ; 
 int /*<<< orphan*/  visor_mouse_channel_guid ; 
 int /*<<< orphan*/  visorbus_disable_channel_interrupts (struct visor_device*) ; 
 int /*<<< orphan*/ * visorchannel_get_guid (int /*<<< orphan*/ ) ; 
 int visorinput_keyboard ; 
 int visorinput_mouse ; 

__attribute__((used)) static int visorinput_probe(struct visor_device *dev)
{
	const guid_t *guid;
	enum visorinput_dev_type dtype;

	guid = visorchannel_get_guid(dev->visorchannel);
	if (guid_equal(guid, &visor_mouse_channel_guid))
		dtype = visorinput_mouse;
	else if (guid_equal(guid, &visor_keyboard_channel_guid))
		dtype = visorinput_keyboard;
	else
		return -ENODEV;
	visorbus_disable_channel_interrupts(dev);
	if (!devdata_create(dev, dtype))
		return -ENOMEM;
	return 0;
}