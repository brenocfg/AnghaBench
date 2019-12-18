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
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_flash_address (struct docg3*,int) ; 

__attribute__((used)) static void doc_setup_writeaddr_sector(struct docg3 *docg3, int sector, int ofs)
{
	ofs = ofs >> 2;
	doc_delay(docg3, 1);
	doc_flash_address(docg3, ofs & 0xff);
	doc_flash_address(docg3, sector & 0xff);
	doc_flash_address(docg3, (sector >> 8) & 0xff);
	doc_flash_address(docg3, (sector >> 16) & 0xff);
	doc_delay(docg3, 1);
}