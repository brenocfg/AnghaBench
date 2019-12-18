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
struct bcm47xxsflash {int type; int (* cc_read ) (struct bcm47xxsflash*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  BCM47XXSFLASH_TYPE_ATMEL 129 
#define  BCM47XXSFLASH_TYPE_ST 128 
 int /*<<< orphan*/  BCMA_CC_FLASHDATA ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_AT_STATUS ; 
 int /*<<< orphan*/  OPCODE_ST_RDSR ; 
 int SR_AT_READY ; 
 int SR_ST_WIP ; 
 int /*<<< orphan*/  bcm47xxsflash_cmd (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 
 int stub2 (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after_eq (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bcm47xxsflash_poll(struct bcm47xxsflash *b47s, int timeout)
{
	unsigned long deadline = jiffies + timeout;

	do {
		switch (b47s->type) {
		case BCM47XXSFLASH_TYPE_ST:
			bcm47xxsflash_cmd(b47s, OPCODE_ST_RDSR);
			if (!(b47s->cc_read(b47s, BCMA_CC_FLASHDATA) &
			      SR_ST_WIP))
				return 0;
			break;
		case BCM47XXSFLASH_TYPE_ATMEL:
			bcm47xxsflash_cmd(b47s, OPCODE_AT_STATUS);
			if (b47s->cc_read(b47s, BCMA_CC_FLASHDATA) &
			    SR_AT_READY)
				return 0;
			break;
		}

		cpu_relax();
		udelay(1);
	} while (!time_after_eq(jiffies, deadline));

	pr_err("Timeout waiting for flash to be ready!\n");

	return -EBUSY;
}