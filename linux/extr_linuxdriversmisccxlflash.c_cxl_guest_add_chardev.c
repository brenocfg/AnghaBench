#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  devt; } ;
struct cxl {TYPE_2__ dev; int /*<<< orphan*/  adapter_num; TYPE_1__* guest; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_3__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_CARD_MINOR (struct cxl*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxl_get_dev () ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fops ; 
 int /*<<< orphan*/  sem ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

int cxl_guest_add_chardev(struct cxl *adapter)
{
	dev_t devt;
	int rc;

	devt = MKDEV(MAJOR(cxl_get_dev()), CXL_CARD_MINOR(adapter));
	cdev_init(&adapter->guest->cdev, &fops);
	if ((rc = cdev_add(&adapter->guest->cdev, devt, 1))) {
		dev_err(&adapter->dev,
			"Unable to add chardev on adapter (card%i): %i\n",
			adapter->adapter_num, rc);
		goto err;
	}
	adapter->dev.devt = devt;
	sema_init(&sem, 1);
err:
	return rc;
}