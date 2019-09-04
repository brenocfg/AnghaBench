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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP22_RSS_TABLE_ENTRIES ; 
 scalar_t__ mvpp22_rss_is_supported () ; 

__attribute__((used)) static u32 mvpp2_ethtool_get_rxfh_indir_size(struct net_device *dev)
{
	return mvpp22_rss_is_supported() ? MVPP22_RSS_TABLE_ENTRIES : 0;
}