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
struct enic {int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENIC_RSS_LEN ; 
 int __enic_set_rsskey (struct enic*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_set_rsskey(struct enic *enic)
{
	netdev_rss_key_fill(enic->rss_key, ENIC_RSS_LEN);

	return __enic_set_rsskey(enic);
}