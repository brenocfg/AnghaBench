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
struct nand_subop {TYPE_3__* instrs; } ;
struct nand_chip {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  timeout_ms; } ;
struct TYPE_5__ {TYPE_1__ waitrdy; } ;
struct TYPE_6__ {TYPE_2__ ctx; } ;

/* Variables and functions */
 int nand_soft_waitrdy (struct nand_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_nfc_soft_waitrdy(struct nand_chip *nand,
				  const struct nand_subop *subop)
{
	return nand_soft_waitrdy(nand,
				 subop->instrs[0].ctx.waitrdy.timeout_ms);
}