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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mv643xx_eth_stats ; 

__attribute__((used)) static void mv643xx_eth_get_strings(struct net_device *dev,
				    uint32_t stringset, uint8_t *data)
{
	int i;

	if (stringset == ETH_SS_STATS) {
		for (i = 0; i < ARRAY_SIZE(mv643xx_eth_stats); i++) {
			memcpy(data + i * ETH_GSTRING_LEN,
				mv643xx_eth_stats[i].stat_string,
				ETH_GSTRING_LEN);
		}
	}
}