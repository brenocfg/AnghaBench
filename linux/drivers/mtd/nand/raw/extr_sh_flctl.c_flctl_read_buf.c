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
struct sh_flctl {size_t index; int /*<<< orphan*/ * done_buff; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct sh_flctl* mtd_to_flctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void flctl_read_buf(struct nand_chip *chip, uint8_t *buf, int len)
{
	struct sh_flctl *flctl = mtd_to_flctl(nand_to_mtd(chip));

	memcpy(buf, &flctl->done_buff[flctl->index], len);
	flctl->index += len;
}