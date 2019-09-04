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
typedef  int u32 ;
struct bcm47xxsflash {int (* cc_read ) (struct bcm47xxsflash*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cc_write ) (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_FLASHCTL ; 
 int BCMA_CC_FLASHCTL_BUSY ; 
 int BCMA_CC_FLASHCTL_START ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct bcm47xxsflash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm47xxsflash_cmd(struct bcm47xxsflash *b47s, u32 opcode)
{
	int i;

	b47s->cc_write(b47s, BCMA_CC_FLASHCTL, BCMA_CC_FLASHCTL_START | opcode);
	for (i = 0; i < 1000; i++) {
		if (!(b47s->cc_read(b47s, BCMA_CC_FLASHCTL) &
		      BCMA_CC_FLASHCTL_BUSY))
			return;
		cpu_relax();
	}
	pr_err("Control command failed (timeout)!\n");
}