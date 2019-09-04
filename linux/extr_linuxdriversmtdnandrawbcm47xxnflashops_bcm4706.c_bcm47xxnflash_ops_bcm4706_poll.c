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
struct bcma_drv_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_NFLASH_CTL ; 
 int BCMA_CC_NFLASH_CTL_ERR ; 
 int EBUSY ; 
 int NCTL_READY ; 
 int NFLASH_READY_RETRIES ; 
 int bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int bcm47xxnflash_ops_bcm4706_poll(struct bcma_drv_cc *cc)
{
	int i;

	for (i = 0; i < NFLASH_READY_RETRIES; i++) {
		if (bcma_cc_read32(cc, BCMA_CC_NFLASH_CTL) & NCTL_READY) {
			if (bcma_cc_read32(cc, BCMA_CC_NFLASH_CTL) &
			    BCMA_CC_NFLASH_CTL_ERR) {
				pr_err("Error on polling\n");
				return -EBUSY;
			} else {
				return 0;
			}
		}
	}

	pr_err("Polling timeout!\n");
	return -EBUSY;
}