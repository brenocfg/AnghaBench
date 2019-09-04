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

/* Variables and functions */
 int ACP_TILE_DSP2 ; 
 int ACP_TILE_OFF_MASK ; 
 int ACP_TILE_OFF_RETAIN_REG_MASK ; 
 int ACP_TILE_ON_MASK ; 
 int ACP_TILE_P1 ; 
 int ACP_TIMEOUT_LOOP ; 
 int ETIMEDOUT ; 
 int cgs_read_register (void*,scalar_t__) ; 
 int /*<<< orphan*/  cgs_write_register (void*,scalar_t__,int) ; 
 scalar_t__ mmACP_PGFSM_CONFIG_REG ; 
 scalar_t__ mmACP_PGFSM_READ_REG_0 ; 
 scalar_t__ mmACP_PGFSM_RETAIN_REG ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int acp_suspend_tile(void *cgs_dev, int tile)
{
	u32 val = 0;
	u32 count = 0;

	if ((tile  < ACP_TILE_P1) || (tile > ACP_TILE_DSP2)) {
		pr_err("Invalid ACP tile : %d to suspend\n", tile);
		return -1;
	}

	val = cgs_read_register(cgs_dev, mmACP_PGFSM_READ_REG_0 + tile);
	val &= ACP_TILE_ON_MASK;

	if (val == 0x0) {
		val = cgs_read_register(cgs_dev, mmACP_PGFSM_RETAIN_REG);
		val = val | (1 << tile);
		cgs_write_register(cgs_dev, mmACP_PGFSM_RETAIN_REG, val);
		cgs_write_register(cgs_dev, mmACP_PGFSM_CONFIG_REG,
					0x500 + tile);

		count = ACP_TIMEOUT_LOOP;
		while (true) {
			val = cgs_read_register(cgs_dev, mmACP_PGFSM_READ_REG_0
								+ tile);
			val = val & ACP_TILE_ON_MASK;
			if (val == ACP_TILE_OFF_MASK)
				break;
			if (--count == 0) {
				pr_err("Timeout reading ACP PGFSM status\n");
				return -ETIMEDOUT;
			}
			udelay(100);
		}

		val = cgs_read_register(cgs_dev, mmACP_PGFSM_RETAIN_REG);

		val |= ACP_TILE_OFF_RETAIN_REG_MASK;
		cgs_write_register(cgs_dev, mmACP_PGFSM_RETAIN_REG, val);
	}
	return 0;
}