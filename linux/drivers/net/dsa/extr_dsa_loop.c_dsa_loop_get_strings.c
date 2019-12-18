#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u32 ;
struct dsa_switch {struct dsa_loop_priv* priv; } ;
struct dsa_loop_priv {TYPE_2__* ports; } ;
struct TYPE_4__ {TYPE_1__* mib; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_PHY_STATS ; 
 scalar_t__ ETH_SS_STATS ; 
 unsigned int __DSA_LOOP_CNT_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void dsa_loop_get_strings(struct dsa_switch *ds, int port,
				 u32 stringset, uint8_t *data)
{
	struct dsa_loop_priv *ps = ds->priv;
	unsigned int i;

	if (stringset != ETH_SS_STATS && stringset != ETH_SS_PHY_STATS)
		return;

	for (i = 0; i < __DSA_LOOP_CNT_MAX; i++)
		memcpy(data + i * ETH_GSTRING_LEN,
		       ps->ports[port].mib[i].name, ETH_GSTRING_LEN);
}