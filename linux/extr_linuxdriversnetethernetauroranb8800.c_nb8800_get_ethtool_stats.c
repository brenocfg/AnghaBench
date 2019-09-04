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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int NB8800_NUM_STATS ; 
 int /*<<< orphan*/  nb8800_read_stat (struct net_device*,unsigned int) ; 

__attribute__((used)) static void nb8800_get_ethtool_stats(struct net_device *dev,
				     struct ethtool_stats *estats, u64 *st)
{
	unsigned int i;
	u32 rx, tx;

	for (i = 0; i < NB8800_NUM_STATS / 2; i++) {
		rx = nb8800_read_stat(dev, i);
		tx = nb8800_read_stat(dev, i | 0x80);
		st[i] = rx;
		st[i + NB8800_NUM_STATS / 2] = tx;
	}
}