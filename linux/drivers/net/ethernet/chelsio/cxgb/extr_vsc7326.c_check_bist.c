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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int bist_rd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 

__attribute__((used)) static int check_bist(adapter_t *adapter, int moduleid)
{
	int result=0;
	int column=0;
	/*check bist*/
	result = bist_rd(adapter,moduleid, 0x02);
	column = ((bist_rd(adapter,moduleid, 0x0e)<<8) +
			(bist_rd(adapter,moduleid, 0x0d)));
	if ((result & 3) != 0x3)
		pr_err("Result: 0x%x  BIST error in ram %d, column: 0x%04x\n",
			result, moduleid, column);
	return 0;
}