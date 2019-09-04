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
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mvneta_statistics ; 

__attribute__((used)) static void mvneta_ethtool_get_strings(struct net_device *netdev, u32 sset,
				       u8 *data)
{
	if (sset == ETH_SS_STATS) {
		int i;

		for (i = 0; i < ARRAY_SIZE(mvneta_statistics); i++)
			memcpy(data + i * ETH_GSTRING_LEN,
			       mvneta_statistics[i].name, ETH_GSTRING_LEN);
	}
}