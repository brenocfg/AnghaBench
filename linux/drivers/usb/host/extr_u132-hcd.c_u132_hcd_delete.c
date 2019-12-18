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
struct usb_hcd {int dummy; } ;
struct u132 {int going; struct platform_device* platform_dev; int /*<<< orphan*/  u132_list; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,struct usb_hcd*,struct u132*,int,struct platform_device*) ; 
 struct u132* kref_to_u132 (struct kref*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int u132_instances ; 
 int /*<<< orphan*/  u132_module_lock ; 
 struct usb_hcd* u132_to_hcd (struct u132*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static void u132_hcd_delete(struct kref *kref)
{
	struct u132 *u132 = kref_to_u132(kref);
	struct platform_device *pdev = u132->platform_dev;
	struct usb_hcd *hcd = u132_to_hcd(u132);
	u132->going += 1;
	mutex_lock(&u132_module_lock);
	list_del_init(&u132->u132_list);
	u132_instances -= 1;
	mutex_unlock(&u132_module_lock);
	dev_warn(&u132->platform_dev->dev, "FREEING the hcd=%p and thus the u13"
		"2=%p going=%d pdev=%p\n", hcd, u132, u132->going, pdev);
	usb_put_hcd(hcd);
}