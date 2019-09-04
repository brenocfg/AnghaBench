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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {int media; int tx_enable; int timeout; int autosense; int c_media; int /*<<< orphan*/  local_state; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  AUI 137 
 int AUTO ; 
#define  BNC 136 
#define  BNC_AUI 135 
#define  BNC_AUI_SUSPECT 134 
 int DE4X5_AUTOSENSE_MS ; 
 int /*<<< orphan*/  DISABLE_IRQs ; 
#define  EXT_SIA 133 
#define  EXT_SIA_SUSPECT 132 
#define  INIT 131 
#define  NC 130 
#define  TP 129 
#define  TP_SUSPECT 128 
 int dc21040_state (struct net_device*,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de4x5_dbg_media (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_save_skbs (struct net_device*) ; 
 int de4x5_suspect_state (struct net_device*,int,int const,int /*<<< orphan*/ ,int (*) (struct net_device*)) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ping_media ; 
 int /*<<< orphan*/  reset_init_sia (struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  test_tp ; 

__attribute__((used)) static int
dc21040_autoconf(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int next_tick = DE4X5_AUTOSENSE_MS;
    s32 imr;

    switch (lp->media) {
    case INIT:
	DISABLE_IRQs;
	lp->tx_enable = false;
	lp->timeout = -1;
	de4x5_save_skbs(dev);
	if ((lp->autosense == AUTO) || (lp->autosense == TP)) {
	    lp->media = TP;
	} else if ((lp->autosense == BNC) || (lp->autosense == AUI) || (lp->autosense == BNC_AUI)) {
	    lp->media = BNC_AUI;
	} else if (lp->autosense == EXT_SIA) {
	    lp->media = EXT_SIA;
	} else {
	    lp->media = NC;
	}
	lp->local_state = 0;
	next_tick = dc21040_autoconf(dev);
	break;

    case TP:
	next_tick = dc21040_state(dev, 0x8f01, 0xffff, 0x0000, 3000, BNC_AUI,
		                                         TP_SUSPECT, test_tp);
	break;

    case TP_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, TP, test_tp, dc21040_autoconf);
	break;

    case BNC:
    case AUI:
    case BNC_AUI:
	next_tick = dc21040_state(dev, 0x8f09, 0x0705, 0x0006, 3000, EXT_SIA,
		                                  BNC_AUI_SUSPECT, ping_media);
	break;

    case BNC_AUI_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, BNC_AUI, ping_media, dc21040_autoconf);
	break;

    case EXT_SIA:
	next_tick = dc21040_state(dev, 0x3041, 0x0000, 0x0006, 3000,
		                              NC, EXT_SIA_SUSPECT, ping_media);
	break;

    case EXT_SIA_SUSPECT:
	next_tick = de4x5_suspect_state(dev, 1000, EXT_SIA, ping_media, dc21040_autoconf);
	break;

    case NC:
	/* default to TP for all */
	reset_init_sia(dev, 0x8f01, 0xffff, 0x0000);
	if (lp->media != lp->c_media) {
	    de4x5_dbg_media(dev);
	    lp->c_media = lp->media;
	}
	lp->media = INIT;
	lp->tx_enable = false;
	break;
    }

    return next_tick;
}