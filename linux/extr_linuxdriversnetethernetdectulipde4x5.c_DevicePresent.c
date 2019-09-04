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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int dummy; } ;
struct de4x5_srom {int dummy; } ;
struct de4x5_private {scalar_t__ chipset; scalar_t__ bus; int /*<<< orphan*/  srom; } ;
typedef  void* __le16 ;

/* Variables and functions */
 scalar_t__ DC21040 ; 
 scalar_t__ EISA ; 
 int ETH_ALEN ; 
 int SROM_HWADD ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  de4x5_dbg_srom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_addr_rst (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ srom_rd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
DevicePresent(struct net_device *dev, u_long aprom_addr)
{
    int i, j=0;
    struct de4x5_private *lp = netdev_priv(dev);

    if (lp->chipset == DC21040) {
	if (lp->bus == EISA) {
	    enet_addr_rst(aprom_addr); /* Reset Ethernet Address ROM Pointer */
	} else {
	    outl(0, aprom_addr);       /* Reset Ethernet Address ROM Pointer */
	}
    } else {                           /* Read new srom */
	u_short tmp;
	__le16 *p = (__le16 *)((char *)&lp->srom + SROM_HWADD);
	for (i=0; i<(ETH_ALEN>>1); i++) {
	    tmp = srom_rd(aprom_addr, (SROM_HWADD>>1) + i);
	    j += tmp;	/* for check for 0:0:0:0:0:0 or ff:ff:ff:ff:ff:ff */
	    *p = cpu_to_le16(tmp);
	}
	if (j == 0 || j == 3 * 0xffff) {
		/* could get 0 only from all-0 and 3 * 0xffff only from all-1 */
		return;
	}

	p = (__le16 *)&lp->srom;
	for (i=0; i<(sizeof(struct de4x5_srom)>>1); i++) {
	    tmp = srom_rd(aprom_addr, i);
	    *p++ = cpu_to_le16(tmp);
	}
	de4x5_dbg_srom(&lp->srom);
    }
}