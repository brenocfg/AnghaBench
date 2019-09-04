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
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int DSAF_PPE_INODE_BASE ; 
 int ETH_SS_STATS ; 
 char* hns_dsaf_get_node_stats_strings (char*,int,struct dsaf_device*) ; 

void hns_dsaf_get_strings(int stringset, u8 *data, int port,
			  struct dsaf_device *dsaf_dev)
{
	char *buff = (char *)data;
	int node = port;

	if (stringset != ETH_SS_STATS)
		return;

	/* for ge/xge node info */
	buff = hns_dsaf_get_node_stats_strings(buff, node, dsaf_dev);

	/* for ppe node info */
	node = port + DSAF_PPE_INODE_BASE;
	(void)hns_dsaf_get_node_stats_strings(buff, node, dsaf_dev);
}