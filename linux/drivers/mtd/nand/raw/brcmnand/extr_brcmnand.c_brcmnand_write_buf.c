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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int dummy; } ;
struct brcmnand_host {int last_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  LL_OP_WR ; 
#define  NAND_CMD_SET_FEATURES 128 
 int /*<<< orphan*/  brcmnand_low_level_op (struct brcmnand_host*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void brcmnand_write_buf(struct nand_chip *chip, const uint8_t *buf,
			       int len)
{
	int i;
	struct brcmnand_host *host = nand_get_controller_data(chip);

	switch (host->last_cmd) {
	case NAND_CMD_SET_FEATURES:
		for (i = 0; i < len; i++)
			brcmnand_low_level_op(host, LL_OP_WR, buf[i],
						  (i + 1) == len);
		break;
	default:
		BUG();
		break;
	}
}