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

/* Variables and functions */
 int /*<<< orphan*/  denali_write_buf (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void denali_write_byte(struct mtd_info *mtd, uint8_t byte)
{
	denali_write_buf(mtd, &byte, 1);
}