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
struct stmmac_priv {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*) ; 
 int stmmac_selftest_get_count (struct stmmac_priv*) ; 
 TYPE_1__* stmmac_selftests ; 

void stmmac_selftest_get_strings(struct stmmac_priv *priv, u8 *data)
{
	u8 *p = data;
	int i;

	for (i = 0; i < stmmac_selftest_get_count(priv); i++) {
		snprintf(p, ETH_GSTRING_LEN, "%2d. %s", i + 1,
			 stmmac_selftests[i].name);
		p += ETH_GSTRING_LEN;
	}
}