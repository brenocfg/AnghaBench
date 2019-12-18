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
typedef  int u16 ;
struct usb_hub_descriptor {int dummy; } ;
struct usb_hcd {int dummy; } ;
struct u132 {int going; int /*<<< orphan*/  sw_lock; TYPE_1__* platform_dev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  C_HUB_LOCAL_POWER 136 
#define  C_HUB_OVER_CURRENT 135 
#define  ClearHubFeature 134 
#define  ClearPortFeature 133 
 int ENODEV ; 
 int EPIPE ; 
 int ESHUTDOWN ; 
#define  GetHubDescriptor 132 
#define  GetHubStatus 131 
#define  GetPortStatus 130 
#define  SetHubFeature 129 
#define  SetPortFeature 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct u132* hcd_to_u132 (struct usb_hcd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u132_disable (struct u132*) ; 
 int u132_roothub_clearportfeature (struct u132*,int,int) ; 
 int u132_roothub_descriptor (struct u132*,struct usb_hub_descriptor*) ; 
 int u132_roothub_portstatus (struct u132*,int /*<<< orphan*/ *,int) ; 
 int u132_roothub_setportfeature (struct u132*,int,int) ; 
 int u132_roothub_status (struct u132*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int u132_hub_control(struct usb_hcd *hcd, u16 typeReq, u16 wValue,
	u16 wIndex, char *buf, u16 wLength)
{
	struct u132 *u132 = hcd_to_u132(hcd);
	if (u132->going > 1) {
		dev_err(&u132->platform_dev->dev, "device has been removed %d\n"
			, u132->going);
		return -ENODEV;
	} else if (u132->going > 0) {
		dev_err(&u132->platform_dev->dev, "device is being removed\n");
		return -ESHUTDOWN;
	} else {
		int retval = 0;
		mutex_lock(&u132->sw_lock);
		switch (typeReq) {
		case ClearHubFeature:
			switch (wValue) {
			case C_HUB_OVER_CURRENT:
			case C_HUB_LOCAL_POWER:
				break;
			default:
				goto stall;
			}
			break;
		case SetHubFeature:
			switch (wValue) {
			case C_HUB_OVER_CURRENT:
			case C_HUB_LOCAL_POWER:
				break;
			default:
				goto stall;
			}
			break;
		case ClearPortFeature:{
				retval = u132_roothub_clearportfeature(u132,
					wValue, wIndex);
				if (retval)
					goto error;
				break;
			}
		case GetHubDescriptor:{
				retval = u132_roothub_descriptor(u132,
					(struct usb_hub_descriptor *)buf);
				if (retval)
					goto error;
				break;
			}
		case GetHubStatus:{
				retval = u132_roothub_status(u132,
					(__le32 *) buf);
				if (retval)
					goto error;
				break;
			}
		case GetPortStatus:{
				retval = u132_roothub_portstatus(u132,
					(__le32 *) buf, wIndex);
				if (retval)
					goto error;
				break;
			}
		case SetPortFeature:{
				retval = u132_roothub_setportfeature(u132,
					wValue, wIndex);
				if (retval)
					goto error;
				break;
			}
		default:
			goto stall;
		error:
			u132_disable(u132);
			u132->going = 1;
			break;
		stall:
			retval = -EPIPE;
			break;
		}
		mutex_unlock(&u132->sw_lock);
		return retval;
	}
}