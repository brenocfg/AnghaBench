#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int clock_type; int /*<<< orphan*/  clock_rate; scalar_t__ loopback; } ;
typedef  TYPE_3__ sync_serial_settings ;
typedef  int /*<<< orphan*/  sync ;
struct TYPE_6__ {int /*<<< orphan*/  sync; } ;
struct TYPE_7__ {int size; int type; TYPE_1__ ifs_ifsu; } ;
struct ifreq {TYPE_2__ ifr_settings; } ;
struct fst_port_info {int index; void* hwif; } ;
struct fst_card_info {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  lineSpeed; int /*<<< orphan*/  internalClock; int /*<<< orphan*/  lineInterface; } ;

/* Variables and functions */
#define  CLOCK_EXT 136 
#define  CLOCK_INT 135 
 void* E1 ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTCLK ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_WRL (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_WRW (struct fst_card_info*,int /*<<< orphan*/ ,void*) ; 
#define  IF_IFACE_E1 134 
#define  IF_IFACE_SYNC_SERIAL 133 
#define  IF_IFACE_T1 132 
#define  IF_IFACE_V24 131 
#define  IF_IFACE_V35 130 
#define  IF_IFACE_X21 129 
#define  IF_IFACE_X21D 128 
 int /*<<< orphan*/  INTCLK ; 
 void* T1 ; 
 void* V24 ; 
 void* V35 ; 
 void* X21 ; 
 void* X21D ; 
 scalar_t__ copy_from_user (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* portConfig ; 

__attribute__((used)) static int
fst_set_iface(struct fst_card_info *card, struct fst_port_info *port,
	      struct ifreq *ifr)
{
	sync_serial_settings sync;
	int i;

	if (ifr->ifr_settings.size != sizeof (sync)) {
		return -ENOMEM;
	}

	if (copy_from_user
	    (&sync, ifr->ifr_settings.ifs_ifsu.sync, sizeof (sync))) {
		return -EFAULT;
	}

	if (sync.loopback)
		return -EINVAL;

	i = port->index;

	switch (ifr->ifr_settings.type) {
	case IF_IFACE_V35:
		FST_WRW(card, portConfig[i].lineInterface, V35);
		port->hwif = V35;
		break;

	case IF_IFACE_V24:
		FST_WRW(card, portConfig[i].lineInterface, V24);
		port->hwif = V24;
		break;

	case IF_IFACE_X21:
		FST_WRW(card, portConfig[i].lineInterface, X21);
		port->hwif = X21;
		break;

	case IF_IFACE_X21D:
		FST_WRW(card, portConfig[i].lineInterface, X21D);
		port->hwif = X21D;
		break;

	case IF_IFACE_T1:
		FST_WRW(card, portConfig[i].lineInterface, T1);
		port->hwif = T1;
		break;

	case IF_IFACE_E1:
		FST_WRW(card, portConfig[i].lineInterface, E1);
		port->hwif = E1;
		break;

	case IF_IFACE_SYNC_SERIAL:
		break;

	default:
		return -EINVAL;
	}

	switch (sync.clock_type) {
	case CLOCK_EXT:
		FST_WRB(card, portConfig[i].internalClock, EXTCLK);
		break;

	case CLOCK_INT:
		FST_WRB(card, portConfig[i].internalClock, INTCLK);
		break;

	default:
		return -EINVAL;
	}
	FST_WRL(card, portConfig[i].lineSpeed, sync.clock_rate);
	return 0;
}