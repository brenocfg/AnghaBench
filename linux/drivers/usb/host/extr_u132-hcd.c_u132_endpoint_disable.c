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
struct usb_host_endpoint {struct u132_endp* hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct u132_endp {int dummy; } ;
struct u132 {int going; TYPE_1__* platform_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct u132*,struct usb_hcd*,struct usb_host_endpoint*,int) ; 
 struct u132* hcd_to_u132 (struct usb_hcd*) ; 
 int /*<<< orphan*/  u132_endp_put_kref (struct u132*,struct u132_endp*) ; 

__attribute__((used)) static void u132_endpoint_disable(struct usb_hcd *hcd,
	struct usb_host_endpoint *hep)
{
	struct u132 *u132 = hcd_to_u132(hcd);
	if (u132->going > 2) {
		dev_err(&u132->platform_dev->dev, "u132 device %p(hcd=%p hep=%p"
			") has been removed %d\n", u132, hcd, hep,
			u132->going);
	} else {
		struct u132_endp *endp = hep->hcpriv;
		if (endp)
			u132_endp_put_kref(u132, endp);
	}
}