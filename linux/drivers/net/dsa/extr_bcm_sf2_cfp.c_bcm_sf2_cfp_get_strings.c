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
typedef  scalar_t__ u32 ;
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {unsigned int num_cfp_rules; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 TYPE_1__* bcm_sf2_cfp_stats ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char*,int) ; 

void bcm_sf2_cfp_get_strings(struct dsa_switch *ds, int port,
			     u32 stringset, uint8_t *data)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	unsigned int s = ARRAY_SIZE(bcm_sf2_cfp_stats);
	char buf[ETH_GSTRING_LEN];
	unsigned int i, j, iter;

	if (stringset != ETH_SS_STATS)
		return;

	for (i = 1; i < priv->num_cfp_rules; i++) {
		for (j = 0; j < s; j++) {
			snprintf(buf, sizeof(buf),
				 "CFP%03d_%sCntr",
				 i, bcm_sf2_cfp_stats[j].name);
			iter = (i - 1) * s + j;
			strlcpy(data + iter * ETH_GSTRING_LEN,
				buf, ETH_GSTRING_LEN);
		}
	}
}