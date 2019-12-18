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
typedef  int u32 ;
struct xlr_net_priv {int /*<<< orphan*/  base_addr; TYPE_2__* ndev; TYPE_1__* nd; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int cpu_mask; } ;

/* Variables and functions */
 scalar_t__ R_TRANSLATETABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  xlr_nae_wreg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void xlr_config_translate_table(struct xlr_net_priv *priv)
{
	u32 cpu_mask;
	u32 val;
	int bkts[32]; /* one bucket is assumed for each cpu */
	int b1, b2, c1, c2, i, j, k;
	int use_bkt;

	use_bkt = 0;
	cpu_mask = priv->nd->cpu_mask;

	pr_info("Using %s-based distribution\n",
		(use_bkt) ? "bucket" : "class");
	j = 0;
	for (i = 0; i < 32; i++) {
		if ((1 << i) & cpu_mask) {
			/* for each cpu, mark the 4+threadid bucket */
			bkts[j] = ((i / 4) * 8) + (i % 4);
			j++;
		}
	}

	/*configure the 128 * 9 Translation table to send to available buckets*/
	k = 0;
	c1 = 3;
	c2 = 0;
	for (i = 0; i < 64; i++) {
		/*
		 * On use_bkt set the b0, b1 are used, else
		 * the 4 classes are used, here implemented
		 * a logic to distribute the packets to the
		 * buckets equally or based on the class
		 */
		c1 = (c1 + 1) & 3;
		c2 = (c1 + 1) & 3;
		b1 = bkts[k];
		k = (k + 1) % j;
		b2 = bkts[k];
		k = (k + 1) % j;

		val = ((c1 << 23) | (b1 << 17) | (use_bkt << 16) |
				(c2 << 7) | (b2 << 1) | (use_bkt << 0));
		dev_dbg(&priv->ndev->dev, "Table[%d] b1=%d b2=%d c1=%d c2=%d\n",
			i, b1, b2, c1, c2);
		xlr_nae_wreg(priv->base_addr, R_TRANSLATETABLE + i, val);
		c1 = c2;
	}
}