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
struct map_info {int /*<<< orphan*/  name; struct cfi_private* fldrv_priv; } ;
struct flchip {int /*<<< orphan*/  start; } ;
struct cfi_private {int /*<<< orphan*/  device_type; int /*<<< orphan*/  addr_unlock1; } ;
typedef  int /*<<< orphan*/  map_word ;

/* Variables and functions */
 unsigned long CFI_SR_ESB ; 
 unsigned long CFI_SR_PSB ; 
 unsigned long CFI_SR_SLSB ; 
 unsigned long CFI_SR_WBASB ; 
 int /*<<< orphan*/  CMD (int) ; 
 unsigned long MERGESTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfi_send_gen_cmd (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct map_info*,struct cfi_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfi_use_status_reg (struct cfi_private*) ; 
 int /*<<< orphan*/  map_read (struct map_info*,unsigned long) ; 
 scalar_t__ map_word_bitsset (struct map_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void cfi_check_err_status(struct map_info *map, struct flchip *chip,
				 unsigned long adr)
{
	struct cfi_private *cfi = map->fldrv_priv;
	map_word status;

	if (!cfi_use_status_reg(cfi))
		return;

	cfi_send_gen_cmd(0x70, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, NULL);
	status = map_read(map, adr);

	if (map_word_bitsset(map, status, CMD(0x3a))) {
		unsigned long chipstatus = MERGESTATUS(status);

		if (chipstatus & CFI_SR_ESB)
			pr_err("%s erase operation failed, status %lx\n",
			       map->name, chipstatus);
		if (chipstatus & CFI_SR_PSB)
			pr_err("%s program operation failed, status %lx\n",
			       map->name, chipstatus);
		if (chipstatus & CFI_SR_WBASB)
			pr_err("%s buffer program command aborted, status %lx\n",
			       map->name, chipstatus);
		if (chipstatus & CFI_SR_SLSB)
			pr_err("%s sector write protected, status %lx\n",
			       map->name, chipstatus);
	}
}