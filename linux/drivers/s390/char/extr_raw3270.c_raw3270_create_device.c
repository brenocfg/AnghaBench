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
struct raw3270 {struct raw3270* ascebc; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct raw3270* ERR_PTR (int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct raw3270*) ; 
 char* kmalloc (int,int) ; 
 struct raw3270* kzalloc (int,int) ; 
 int raw3270_setup_device (struct ccw_device*,struct raw3270*,char*) ; 

__attribute__((used)) static struct raw3270 *
raw3270_create_device(struct ccw_device *cdev)
{
	struct raw3270 *rp;
	char *ascebc;
	int rc;

	rp = kzalloc(sizeof(struct raw3270), GFP_KERNEL | GFP_DMA);
	if (!rp)
		return ERR_PTR(-ENOMEM);
	ascebc = kmalloc(256, GFP_KERNEL);
	if (!ascebc) {
		kfree(rp);
		return ERR_PTR(-ENOMEM);
	}
	rc = raw3270_setup_device(cdev, rp, ascebc);
	if (rc) {
		kfree(rp->ascebc);
		kfree(rp);
		rp = ERR_PTR(rc);
	}
	/* Get reference to ccw_device structure. */
	get_device(&cdev->dev);
	return rp;
}