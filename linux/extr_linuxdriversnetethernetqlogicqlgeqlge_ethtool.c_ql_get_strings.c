#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int QLGE_STATS_LEN ; 
 int QLGE_TEST_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ql_gstrings_stats ; 
 int /*<<< orphan*/ * ql_gstrings_test ; 

__attribute__((used)) static void ql_get_strings(struct net_device *dev, u32 stringset, u8 *buf)
{
	int index;
	switch (stringset) {
	case ETH_SS_TEST:
		memcpy(buf, *ql_gstrings_test, QLGE_TEST_LEN * ETH_GSTRING_LEN);
		break;
	case ETH_SS_STATS:
		for (index = 0; index < QLGE_STATS_LEN; index++) {
			memcpy(buf + index * ETH_GSTRING_LEN,
				ql_gstrings_stats[index].stat_string,
				ETH_GSTRING_LEN);
		}
		break;
	}
}