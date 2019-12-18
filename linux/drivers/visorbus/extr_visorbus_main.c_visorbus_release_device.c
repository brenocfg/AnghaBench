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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct visor_device*) ; 
 struct visor_device* to_visor_device (struct device*) ; 
 int /*<<< orphan*/  visorchannel_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void visorbus_release_device(struct device *xdev)
{
	struct visor_device *dev = to_visor_device(xdev);

	visorchannel_destroy(dev->visorchannel);
	kfree(dev);
}