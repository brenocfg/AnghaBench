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
typedef  int /*<<< orphan*/  u_char ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpc5121_nfc_buf_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void mpc5121_nfc_read_buf(struct nand_chip *chip, u_char *buf, int len)
{
	mpc5121_nfc_buf_copy(nand_to_mtd(chip), buf, len, 0);
}