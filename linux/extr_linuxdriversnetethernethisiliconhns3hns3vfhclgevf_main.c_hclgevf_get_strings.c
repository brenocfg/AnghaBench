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
struct hnae3_handle {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_SS_STATS ; 
 char* hclgevf_tqps_get_strings (struct hnae3_handle*,char*) ; 

__attribute__((used)) static void hclgevf_get_strings(struct hnae3_handle *handle, u32 strset,
				u8 *data)
{
	u8 *p = (char *)data;

	if (strset == ETH_SS_STATS)
		p = hclgevf_tqps_get_strings(handle, p);
}