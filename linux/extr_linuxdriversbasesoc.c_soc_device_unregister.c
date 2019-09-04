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
struct soc_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  soc_dev_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * early_soc_dev_attr ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_ida ; 

void soc_device_unregister(struct soc_device *soc_dev)
{
	ida_simple_remove(&soc_ida, soc_dev->soc_dev_num);

	device_unregister(&soc_dev->dev);
	early_soc_dev_attr = NULL;
}