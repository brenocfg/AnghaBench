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
typedef  unsigned int u8 ;
struct pcmcia_device {int /*<<< orphan*/  dev; struct net_device* priv; } ;
struct net_device {int dummy; } ;
struct local_info {int mohawk; int dingo; int modem; scalar_t__ card_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_MANFID ; 
 scalar_t__ XIR_CE ; 
 scalar_t__ XIR_CE2 ; 
 scalar_t__ XIR_CE3 ; 
 scalar_t__ XIR_CEM ; 
 scalar_t__ XIR_CEM2 ; 
 scalar_t__ XIR_CEM3 ; 
 scalar_t__ XIR_CEM33 ; 
 scalar_t__ XIR_CEM56 ; 
 scalar_t__ XIR_CEM56M ; 
 scalar_t__ XIR_UNKNOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  has_ce2_string (struct pcmcia_device*) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 size_t pcmcia_get_tuple (struct pcmcia_device*,int /*<<< orphan*/ ,unsigned int**) ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 

__attribute__((used)) static int
set_card_type(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    struct local_info *local = netdev_priv(dev);
    u8 *buf;
    unsigned int cisrev, mediaid, prodid;
    size_t len;

    len = pcmcia_get_tuple(link, CISTPL_MANFID, &buf);
    if (len < 5) {
	    dev_err(&link->dev, "invalid CIS -- sorry\n");
	    return 0;
    }

    cisrev = buf[2];
    mediaid = buf[3];
    prodid = buf[4];

    dev_dbg(&link->dev, "cisrev=%02x mediaid=%02x prodid=%02x\n",
	  cisrev, mediaid, prodid);

    local->mohawk = 0;
    local->dingo = 0;
    local->modem = 0;
    local->card_type = XIR_UNKNOWN;
    if (!(prodid & 0x40)) {
	pr_notice("Oops: Not a creditcard\n");
	return 0;
    }
    if (!(mediaid & 0x01)) {
	pr_notice("Not an Ethernet card\n");
	return 0;
    }
    if (mediaid & 0x10) {
	local->modem = 1;
	switch(prodid & 15) {
	  case 1: local->card_type = XIR_CEM   ; break;
	  case 2: local->card_type = XIR_CEM2  ; break;
	  case 3: local->card_type = XIR_CEM3  ; break;
	  case 4: local->card_type = XIR_CEM33 ; break;
	  case 5: local->card_type = XIR_CEM56M;
		  local->mohawk = 1;
		  break;
	  case 6:
	  case 7: /* 7 is the RealPort 10/56 */
		  local->card_type = XIR_CEM56 ;
		  local->mohawk = 1;
		  local->dingo = 1;
		  break;
	}
    } else {
	switch(prodid & 15) {
	  case 1: local->card_type = has_ce2_string(link)? XIR_CE2 : XIR_CE ;
		  break;
	  case 2: local->card_type = XIR_CE2; break;
	  case 3: local->card_type = XIR_CE3;
		  local->mohawk = 1;
		  break;
	}
    }
    if (local->card_type == XIR_CE || local->card_type == XIR_CEM) {
	pr_notice("Sorry, this is an old CE card\n");
	return 0;
    }
    if (local->card_type == XIR_UNKNOWN)
	pr_notice("unknown card (mediaid=%02x prodid=%02x)\n", mediaid, prodid);

    return 1;
}