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
typedef  char u8 ;
typedef  scalar_t__ u32 ;
struct hclge_comm_stats_str {char* desc; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static u8 *hclge_comm_get_strings(u32 stringset,
				  const struct hclge_comm_stats_str strs[],
				  int size, u8 *data)
{
	char *buff = (char *)data;
	u32 i;

	if (stringset != ETH_SS_STATS)
		return buff;

	for (i = 0; i < size; i++) {
		snprintf(buff, ETH_GSTRING_LEN, "%s", strs[i].desc);
		buff = buff + ETH_GSTRING_LEN;
	}

	return (u8 *)buff;
}