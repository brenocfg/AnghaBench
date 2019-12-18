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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ GIGA_MAHR (int) ; 
 scalar_t__ GIGA_MALR (int) ; 
 int /*<<< orphan*/  ioread32 (void*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sh_eth_chip_reset (struct net_device*) ; 

__attribute__((used)) static void sh_eth_chip_reset_giga(struct net_device *ndev)
{
	u32 mahr[2], malr[2];
	int i;

	/* save MAHR and MALR */
	for (i = 0; i < 2; i++) {
		malr[i] = ioread32((void *)GIGA_MALR(i));
		mahr[i] = ioread32((void *)GIGA_MAHR(i));
	}

	sh_eth_chip_reset(ndev);

	/* restore MAHR and MALR */
	for (i = 0; i < 2; i++) {
		iowrite32(malr[i], (void *)GIGA_MALR(i));
		iowrite32(mahr[i], (void *)GIGA_MAHR(i));
	}
}