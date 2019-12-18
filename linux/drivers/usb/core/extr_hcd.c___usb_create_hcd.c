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
struct TYPE_2__ {char const* bus_name; struct device* sysdev; struct device* controller; } ;
struct usb_hcd {int speed; char* product_desc; struct hc_driver const* driver; int /*<<< orphan*/  died_work; int /*<<< orphan*/  wakeup_work; int /*<<< orphan*/  rh_timer; TYPE_1__ self; int /*<<< orphan*/  kref; struct usb_hcd* shared_hcd; struct usb_hcd* primary_hcd; struct usb_hcd* bandwidth_mutex; struct usb_hcd* address0_mutex; } ;
struct hc_driver {int flags; char* product_desc; scalar_t__ hcd_priv_size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HCD_MASK ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct usb_hcd*) ; 
 int /*<<< orphan*/  hcd_died_work ; 
 int /*<<< orphan*/  hcd_resume_work ; 
 int /*<<< orphan*/  kfree (struct usb_hcd*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct usb_hcd* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (struct usb_hcd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rh_timer_func ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_bus_init (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_port_peer_mutex ; 

struct usb_hcd *__usb_create_hcd(const struct hc_driver *driver,
		struct device *sysdev, struct device *dev, const char *bus_name,
		struct usb_hcd *primary_hcd)
{
	struct usb_hcd *hcd;

	hcd = kzalloc(sizeof(*hcd) + driver->hcd_priv_size, GFP_KERNEL);
	if (!hcd)
		return NULL;
	if (primary_hcd == NULL) {
		hcd->address0_mutex = kmalloc(sizeof(*hcd->address0_mutex),
				GFP_KERNEL);
		if (!hcd->address0_mutex) {
			kfree(hcd);
			dev_dbg(dev, "hcd address0 mutex alloc failed\n");
			return NULL;
		}
		mutex_init(hcd->address0_mutex);
		hcd->bandwidth_mutex = kmalloc(sizeof(*hcd->bandwidth_mutex),
				GFP_KERNEL);
		if (!hcd->bandwidth_mutex) {
			kfree(hcd->address0_mutex);
			kfree(hcd);
			dev_dbg(dev, "hcd bandwidth mutex alloc failed\n");
			return NULL;
		}
		mutex_init(hcd->bandwidth_mutex);
		dev_set_drvdata(dev, hcd);
	} else {
		mutex_lock(&usb_port_peer_mutex);
		hcd->address0_mutex = primary_hcd->address0_mutex;
		hcd->bandwidth_mutex = primary_hcd->bandwidth_mutex;
		hcd->primary_hcd = primary_hcd;
		primary_hcd->primary_hcd = primary_hcd;
		hcd->shared_hcd = primary_hcd;
		primary_hcd->shared_hcd = hcd;
		mutex_unlock(&usb_port_peer_mutex);
	}

	kref_init(&hcd->kref);

	usb_bus_init(&hcd->self);
	hcd->self.controller = dev;
	hcd->self.sysdev = sysdev;
	hcd->self.bus_name = bus_name;

	timer_setup(&hcd->rh_timer, rh_timer_func, 0);
#ifdef CONFIG_PM
	INIT_WORK(&hcd->wakeup_work, hcd_resume_work);
#endif

	INIT_WORK(&hcd->died_work, hcd_died_work);

	hcd->driver = driver;
	hcd->speed = driver->flags & HCD_MASK;
	hcd->product_desc = (driver->product_desc) ? driver->product_desc :
			"USB Host Controller";
	return hcd;
}