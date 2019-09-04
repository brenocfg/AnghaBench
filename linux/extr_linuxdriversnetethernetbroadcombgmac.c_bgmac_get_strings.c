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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BGMAC_STATS_LEN ; 
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 TYPE_1__* bgmac_get_strings_stats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bgmac_get_strings(struct net_device *dev, u32 stringset,
			      u8 *data)
{
	int i;

	if (stringset != ETH_SS_STATS)
		return;

	for (i = 0; i < BGMAC_STATS_LEN; i++)
		strlcpy(data + i * ETH_GSTRING_LEN,
			bgmac_get_strings_stats[i].name, ETH_GSTRING_LEN);
}