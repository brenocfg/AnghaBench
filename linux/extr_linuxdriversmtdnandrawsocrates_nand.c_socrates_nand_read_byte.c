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
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  socrates_nand_read_buf (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8_t socrates_nand_read_byte(struct mtd_info *mtd)
{
	uint8_t byte;
	socrates_nand_read_buf(mtd, &byte, sizeof(byte));
	return byte;
}