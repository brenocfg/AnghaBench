#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int u32 ;
struct mtd_info {struct bcm47xxsflash* priv; } ;
struct bcm47xxsflash {int /*<<< orphan*/  (* cc_write ) (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ;TYPE_3__* bcma_cc; } ;
struct TYPE_6__ {TYPE_2__* core; } ;
struct TYPE_4__ {int rev; } ;
struct TYPE_5__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_FLASHADDR ; 
 int /*<<< orphan*/  BCMA_CC_FLASHCTL ; 
 int /*<<< orphan*/  BCMA_CC_FLASHDATA ; 
 int HZ ; 
 int OPCODE_ST_CSA ; 
 int OPCODE_ST_PP ; 
 int OPCODE_ST_WREN ; 
 int /*<<< orphan*/  bcm47xxsflash_cmd (struct bcm47xxsflash*,int) ; 
 scalar_t__ bcm47xxsflash_poll (struct bcm47xxsflash*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct bcm47xxsflash*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bcm47xxsflash_write_st(struct mtd_info *mtd, u32 offset, size_t len,
				  const u_char *buf)
{
	struct bcm47xxsflash *b47s = mtd->priv;
	int written = 0;

	/* Enable writes */
	bcm47xxsflash_cmd(b47s, OPCODE_ST_WREN);

	/* Write first byte */
	b47s->cc_write(b47s, BCMA_CC_FLASHADDR, offset);
	b47s->cc_write(b47s, BCMA_CC_FLASHDATA, *buf++);

	/* Program page */
	if (b47s->bcma_cc->core->id.rev < 20) {
		bcm47xxsflash_cmd(b47s, OPCODE_ST_PP);
		return 1; /* 1B written */
	}

	/* Program page and set CSA (on newer chips we can continue writing) */
	bcm47xxsflash_cmd(b47s, OPCODE_ST_CSA | OPCODE_ST_PP);
	offset++;
	len--;
	written++;

	while (len > 0) {
		/* Page boundary, another function call is needed */
		if ((offset & 0xFF) == 0)
			break;

		bcm47xxsflash_cmd(b47s, OPCODE_ST_CSA | *buf++);
		offset++;
		len--;
		written++;
	}

	/* All done, drop CSA & poll */
	b47s->cc_write(b47s, BCMA_CC_FLASHCTL, 0);
	udelay(1);
	if (bcm47xxsflash_poll(b47s, HZ / 10))
		pr_err("Flash rejected dropping CSA\n");

	return written;
}