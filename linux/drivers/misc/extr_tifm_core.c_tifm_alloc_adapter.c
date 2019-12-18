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
struct tifm_dev {int dummy; } ;
struct TYPE_2__ {struct device* parent; int /*<<< orphan*/ * class; } ;
struct tifm_adapter {unsigned int num_sockets; int /*<<< orphan*/  lock; TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct tifm_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tifm_adapter_class ; 

struct tifm_adapter *tifm_alloc_adapter(unsigned int num_sockets,
					struct device *dev)
{
	struct tifm_adapter *fm;

	fm = kzalloc(sizeof(struct tifm_adapter)
		     + sizeof(struct tifm_dev*) * num_sockets, GFP_KERNEL);
	if (fm) {
		fm->dev.class = &tifm_adapter_class;
		fm->dev.parent = dev;
		device_initialize(&fm->dev);
		spin_lock_init(&fm->lock);
		fm->num_sockets = num_sockets;
	}
	return fm;
}