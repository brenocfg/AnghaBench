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
struct net_device {int /*<<< orphan*/  name; } ;
struct de4x5_private {scalar_t__ media; scalar_t__ c_media; scalar_t__ fdx; } ;

/* Variables and functions */
 scalar_t__ ANS ; 
 scalar_t__ AUI ; 
 scalar_t__ BNC ; 
 scalar_t__ BNC_AUI ; 
 int DEBUG_MEDIA ; 
 scalar_t__ EXT_SIA ; 
 scalar_t__ NC ; 
 scalar_t__ TP ; 
 scalar_t__ _100Mb ; 
 scalar_t__ _10Mb ; 
 int de4x5_debug ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
de4x5_dbg_media(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);

    if (lp->media != lp->c_media) {
	if (de4x5_debug & DEBUG_MEDIA) {
	    printk("%s: media is %s%s\n", dev->name,
		   (lp->media == NC  ? "unconnected, link down or incompatible connection" :
		    (lp->media == TP  ? "TP" :
		     (lp->media == ANS ? "TP/Nway" :
		      (lp->media == BNC ? "BNC" :
		       (lp->media == AUI ? "AUI" :
			(lp->media == BNC_AUI ? "BNC/AUI" :
			 (lp->media == EXT_SIA ? "EXT SIA" :
			  (lp->media == _100Mb  ? "100Mb/s" :
			   (lp->media == _10Mb   ? "10Mb/s" :
			    "???"
			    ))))))))), (lp->fdx?" full duplex.":"."));
	}
	lp->c_media = lp->media;
    }
}