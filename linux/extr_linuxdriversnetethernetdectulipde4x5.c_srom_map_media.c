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
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int fdx; } ;
struct de4x5_private {int fdx; int infoblock_media; int media; int chipset; TYPE_1__ params; } ;

/* Variables and functions */
#define  ANS 137 
 int AUI ; 
 int BNC ; 
 int DC21140 ; 
 int DC2114x ; 
#define  SROM_100BASEF 136 
#define  SROM_100BASEFF 135 
#define  SROM_100BASET 134 
#define  SROM_100BASET4 133 
#define  SROM_100BASETF 132 
#define  SROM_10BASE2 131 
#define  SROM_10BASE5 130 
#define  SROM_10BASET 129 
#define  SROM_10BASETF 128 
 int TP ; 
 void* _100Mb ; 
 int _10Mb ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
srom_map_media(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);

    lp->fdx = false;
    if (lp->infoblock_media == lp->media)
      return 0;

    switch(lp->infoblock_media) {
      case SROM_10BASETF:
	if (!lp->params.fdx) return -1;
	lp->fdx = true;
	/* fall through */

      case SROM_10BASET:
	if (lp->params.fdx && !lp->fdx) return -1;
	if ((lp->chipset == DC21140) || ((lp->chipset & ~0x00ff) == DC2114x)) {
	    lp->media = _10Mb;
	} else {
	    lp->media = TP;
	}
	break;

      case SROM_10BASE2:
	lp->media = BNC;
	break;

      case SROM_10BASE5:
	lp->media = AUI;
	break;

      case SROM_100BASETF:
        if (!lp->params.fdx) return -1;
	lp->fdx = true;
	/* fall through */

      case SROM_100BASET:
	if (lp->params.fdx && !lp->fdx) return -1;
	lp->media = _100Mb;
	break;

      case SROM_100BASET4:
	lp->media = _100Mb;
	break;

      case SROM_100BASEFF:
	if (!lp->params.fdx) return -1;
	lp->fdx = true;
	/* fall through */

      case SROM_100BASEF:
	if (lp->params.fdx && !lp->fdx) return -1;
	lp->media = _100Mb;
	break;

      case ANS:
	lp->media = ANS;
	lp->fdx = lp->params.fdx;
	break;

      default:
	printk("%s: Bad media code [%d] detected in SROM!\n", dev->name,
	                                                  lp->infoblock_media);
	return -1;
    }

    return 0;
}