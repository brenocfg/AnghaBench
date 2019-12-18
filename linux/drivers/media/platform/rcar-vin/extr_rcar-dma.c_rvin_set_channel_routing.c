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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rvin_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int VNCSI_IFMD_CSI_CHSEL (int /*<<< orphan*/ ) ; 
 int VNCSI_IFMD_DES0 ; 
 int VNCSI_IFMD_DES1 ; 
 int /*<<< orphan*/  VNCSI_IFMD_REG ; 
 int /*<<< orphan*/  VNMC_REG ; 
 int VNMC_VUP ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int rvin_read (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,int) ; 

int rvin_set_channel_routing(struct rvin_dev *vin, u8 chsel)
{
	u32 ifmd, vnmc;
	int ret;

	ret = pm_runtime_get_sync(vin->dev);
	if (ret < 0)
		return ret;

	/* Make register writes take effect immediately. */
	vnmc = rvin_read(vin, VNMC_REG);
	rvin_write(vin, vnmc & ~VNMC_VUP, VNMC_REG);

	ifmd = VNCSI_IFMD_DES1 | VNCSI_IFMD_DES0 | VNCSI_IFMD_CSI_CHSEL(chsel);

	rvin_write(vin, ifmd, VNCSI_IFMD_REG);

	vin_dbg(vin, "Set IFMD 0x%x\n", ifmd);

	/* Restore VNMC. */
	rvin_write(vin, vnmc, VNMC_REG);

	pm_runtime_put(vin->dev);

	return 0;
}