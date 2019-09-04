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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LKPTBLQUEUE0_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LKPTBLQUEUE1_G (int /*<<< orphan*/ ) ; 
 int rd_rss_row (struct adapter*,int,int /*<<< orphan*/ *) ; 
 int t4_chip_rss_size (struct adapter*) ; 

int t4_read_rss(struct adapter *adapter, u16 *map)
{
	int i, ret, nentries;
	u32 val;

	nentries = t4_chip_rss_size(adapter);
	for (i = 0; i < nentries / 2; ++i) {
		ret = rd_rss_row(adapter, i, &val);
		if (ret)
			return ret;
		*map++ = LKPTBLQUEUE0_G(val);
		*map++ = LKPTBLQUEUE1_G(val);
	}
	return 0;
}