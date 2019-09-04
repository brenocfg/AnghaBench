#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 TYPE_1__* mtd ; 
 int mtdtest_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offset ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  wbuffer ; 

__attribute__((used)) static int write_page(int log)
{
	if (log)
		pr_info("write_page\n");

	return mtdtest_write(mtd, offset, mtd->writesize, wbuffer);
}