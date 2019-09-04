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
struct adapter {int dummy; } ;

/* Variables and functions */
 int SF_ERASE_SECTOR ; 
 int SF_WR_ENABLE ; 
 int flash_wait_op (struct adapter*,int,int) ; 
 int sf1_write (struct adapter*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int t3_flash_erase_sectors(struct adapter *adapter, int start, int end)
{
	while (start <= end) {
		int ret;

		if ((ret = sf1_write(adapter, 1, 0, SF_WR_ENABLE)) != 0 ||
		    (ret = sf1_write(adapter, 4, 0,
				     SF_ERASE_SECTOR | (start << 8))) != 0 ||
		    (ret = flash_wait_op(adapter, 5, 500)) != 0)
			return ret;
		start++;
	}
	return 0;
}