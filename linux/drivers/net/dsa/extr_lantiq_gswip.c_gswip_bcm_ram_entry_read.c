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
typedef  int u32 ;
struct gswip_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSWIP_BM_RAM_ADDR ; 
 int /*<<< orphan*/  GSWIP_BM_RAM_CTRL ; 
 int GSWIP_BM_RAM_CTRL_ADDR_MASK ; 
 int GSWIP_BM_RAM_CTRL_BAS ; 
 int GSWIP_BM_RAM_CTRL_OPMOD ; 
 int /*<<< orphan*/  GSWIP_BM_RAM_VAL (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int,int,int /*<<< orphan*/ ) ; 
 int gswip_switch_r (struct gswip_priv*,int /*<<< orphan*/ ) ; 
 int gswip_switch_r_timeout (struct gswip_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gswip_switch_w (struct gswip_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 gswip_bcm_ram_entry_read(struct gswip_priv *priv, u32 table,
				    u32 index)
{
	u32 result;
	int err;

	gswip_switch_w(priv, index, GSWIP_BM_RAM_ADDR);
	gswip_switch_mask(priv, GSWIP_BM_RAM_CTRL_ADDR_MASK |
				GSWIP_BM_RAM_CTRL_OPMOD,
			      table | GSWIP_BM_RAM_CTRL_BAS,
			      GSWIP_BM_RAM_CTRL);

	err = gswip_switch_r_timeout(priv, GSWIP_BM_RAM_CTRL,
				     GSWIP_BM_RAM_CTRL_BAS);
	if (err) {
		dev_err(priv->dev, "timeout while reading table: %u, index: %u",
			table, index);
		return 0;
	}

	result = gswip_switch_r(priv, GSWIP_BM_RAM_VAL(0));
	result |= gswip_switch_r(priv, GSWIP_BM_RAM_VAL(1)) << 16;

	return result;
}