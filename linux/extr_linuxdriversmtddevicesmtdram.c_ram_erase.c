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
struct mtd_info {scalar_t__ priv; } ;
struct erase_info {int addr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check_offs_len (struct mtd_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ram_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	if (check_offs_len(mtd, instr->addr, instr->len))
		return -EINVAL;
	memset((char *)mtd->priv + instr->addr, 0xff, instr->len);

	return 0;
}