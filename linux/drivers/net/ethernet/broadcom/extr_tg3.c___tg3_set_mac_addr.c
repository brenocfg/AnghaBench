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
typedef  int u32 ;
struct tg3 {TYPE_1__* dev; } ;
struct TYPE_2__ {int* dev_addr; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5703 ; 
 scalar_t__ ASIC_REV_5704 ; 
 int /*<<< orphan*/  MAC_TX_BACKOFF_SEED ; 
 int TX_BACKOFF_SEED_MASK ; 
 int /*<<< orphan*/  __tg3_set_one_mac_addr (struct tg3*,int*,int) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __tg3_set_mac_addr(struct tg3 *tp, bool skip_mac_1)
{
	u32 addr_high;
	int i;

	for (i = 0; i < 4; i++) {
		if (i == 1 && skip_mac_1)
			continue;
		__tg3_set_one_mac_addr(tp, tp->dev->dev_addr, i);
	}

	if (tg3_asic_rev(tp) == ASIC_REV_5703 ||
	    tg3_asic_rev(tp) == ASIC_REV_5704) {
		for (i = 4; i < 16; i++)
			__tg3_set_one_mac_addr(tp, tp->dev->dev_addr, i);
	}

	addr_high = (tp->dev->dev_addr[0] +
		     tp->dev->dev_addr[1] +
		     tp->dev->dev_addr[2] +
		     tp->dev->dev_addr[3] +
		     tp->dev->dev_addr[4] +
		     tp->dev->dev_addr[5]) &
		TX_BACKOFF_SEED_MASK;
	tw32(MAC_TX_BACKOFF_SEED, addr_high);
}