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
struct hv_uio_private_data {int /*<<< orphan*/  info; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct hv_uio_private_data* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_uio_cleanup (struct hv_device*,struct hv_uio_private_data*) ; 
 int /*<<< orphan*/  kfree (struct hv_uio_private_data*) ; 
 int /*<<< orphan*/  uio_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_free_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hv_uio_remove(struct hv_device *dev)
{
	struct hv_uio_private_data *pdata = hv_get_drvdata(dev);

	if (!pdata)
		return 0;

	uio_unregister_device(&pdata->info);
	hv_uio_cleanup(dev, pdata);
	hv_set_drvdata(dev, NULL);

	vmbus_free_ring(dev->channel);
	kfree(pdata);
	return 0;
}