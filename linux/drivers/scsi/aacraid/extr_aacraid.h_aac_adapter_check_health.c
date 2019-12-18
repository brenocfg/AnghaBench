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
struct TYPE_2__ {int (* adapter_check_health ) (struct aac_dev*) ;} ;
struct aac_dev {TYPE_1__ a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  aac_pci_offline (struct aac_dev*) ; 
 int stub1 (struct aac_dev*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int aac_adapter_check_health(struct aac_dev *dev)
{
	if (unlikely(aac_pci_offline(dev)))
		return -1;

	return (dev)->a_ops.adapter_check_health(dev);
}