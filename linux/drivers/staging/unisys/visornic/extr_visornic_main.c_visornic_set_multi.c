#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct visornic_devdata {int old_flags; TYPE_3__* dev; } ;
struct TYPE_4__ {int enable; struct net_device* context; } ;
struct TYPE_5__ {TYPE_1__ enbdis; int /*<<< orphan*/  type; } ;
struct uiscmdrsp {TYPE_2__ net; int /*<<< orphan*/  cmdtype; } ;
struct net_device {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  visorchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_NET_TYPE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IOCHAN_TO_IOPART ; 
 int /*<<< orphan*/  NET_RCV_PROMISC ; 
 int /*<<< orphan*/  SIZEOF_CMDRSP ; 
 int /*<<< orphan*/  kfree (struct uiscmdrsp*) ; 
 struct uiscmdrsp* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct visornic_devdata* netdev_priv (struct net_device*) ; 
 int visorchannel_signalinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uiscmdrsp*) ; 

__attribute__((used)) static void visornic_set_multi(struct net_device *netdev)
{
	struct uiscmdrsp *cmdrsp;
	struct visornic_devdata *devdata = netdev_priv(netdev);
	int err = 0;

	if (devdata->old_flags == netdev->flags)
		return;

	if ((netdev->flags & IFF_PROMISC) ==
	    (devdata->old_flags & IFF_PROMISC))
		goto out_save_flags;

	cmdrsp = kmalloc(SIZEOF_CMDRSP, GFP_ATOMIC);
	if (!cmdrsp)
		return;
	cmdrsp->cmdtype = CMD_NET_TYPE;
	cmdrsp->net.type = NET_RCV_PROMISC;
	cmdrsp->net.enbdis.context = netdev;
	cmdrsp->net.enbdis.enable =
		netdev->flags & IFF_PROMISC;
	err = visorchannel_signalinsert(devdata->dev->visorchannel,
					IOCHAN_TO_IOPART,
					cmdrsp);
	kfree(cmdrsp);
	if (err)
		return;

out_save_flags:
	devdata->old_flags = netdev->flags;
}