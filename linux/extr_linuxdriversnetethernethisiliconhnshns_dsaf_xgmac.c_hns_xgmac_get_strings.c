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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {char* desc; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_1__*) ; 
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 TYPE_1__* g_xgmac_stats_string ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 

__attribute__((used)) static void hns_xgmac_get_strings(u32 stringset, u8 *data)
{
	char *buff = (char *)data;
	u32 i;

	if (stringset != ETH_SS_STATS)
		return;

	for (i = 0; i < ARRAY_SIZE(g_xgmac_stats_string); i++) {
		snprintf(buff, ETH_GSTRING_LEN, g_xgmac_stats_string[i].desc);
		buff = buff + ETH_GSTRING_LEN;
	}
}