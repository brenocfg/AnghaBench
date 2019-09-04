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
struct tango_chip {scalar_t__ base; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ PBUS_DATA ; 
 int /*<<< orphan*/  mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  readb_relaxed (scalar_t__) ; 
 struct tango_chip* to_tango_chip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 tango_read_byte(struct mtd_info *mtd)
{
	struct tango_chip *tchip = to_tango_chip(mtd_to_nand(mtd));

	return readb_relaxed(tchip->base + PBUS_DATA);
}