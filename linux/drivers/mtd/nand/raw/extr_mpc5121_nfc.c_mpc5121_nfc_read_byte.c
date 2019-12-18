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
typedef  int /*<<< orphan*/  tmp ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpc5121_nfc_read_buf (struct nand_chip*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 mpc5121_nfc_read_byte(struct nand_chip *chip)
{
	u8 tmp;

	mpc5121_nfc_read_buf(chip, &tmp, sizeof(tmp));

	return tmp;
}