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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int dummy; } ;
typedef  int /*<<< orphan*/  jedecid ;

/* Variables and functions */
 int nand_readid_op (struct nand_chip*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool hynix_nand_has_valid_jedecid(struct nand_chip *chip)
{
	u8 jedecid[5] = { };
	int ret;

	ret = nand_readid_op(chip, 0x40, jedecid, sizeof(jedecid));
	if (ret)
		return false;

	return !strncmp("JEDEC", jedecid, sizeof(jedecid));
}