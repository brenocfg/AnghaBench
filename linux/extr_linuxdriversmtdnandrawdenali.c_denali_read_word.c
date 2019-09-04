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
typedef  int /*<<< orphan*/  uint16_t ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  denali_read_buf16 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t denali_read_word(struct mtd_info *mtd)
{
	uint16_t word;

	denali_read_buf16(mtd, (uint8_t *)&word, 2);

	return word;
}