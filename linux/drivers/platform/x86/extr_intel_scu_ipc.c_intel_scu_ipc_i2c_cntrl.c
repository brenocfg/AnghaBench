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
struct intel_scu_ipc_dev {int /*<<< orphan*/ * dev; scalar_t__ i2c_base; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ I2C_DATA_ADDR ; 
 scalar_t__ IPC_I2C_CNTRL_ADDR ; 
 int IPC_I2C_READ ; 
 int IPC_I2C_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct intel_scu_ipc_dev ipcdev ; 
 int /*<<< orphan*/  ipclock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int intel_scu_ipc_i2c_cntrl(u32 addr, u32 *data)
{
	struct intel_scu_ipc_dev *scu = &ipcdev;
	u32 cmd = 0;

	mutex_lock(&ipclock);
	if (scu->dev == NULL) {
		mutex_unlock(&ipclock);
		return -ENODEV;
	}
	cmd = (addr >> 24) & 0xFF;
	if (cmd == IPC_I2C_READ) {
		writel(addr, scu->i2c_base + IPC_I2C_CNTRL_ADDR);
		/* Write not getting updated without delay */
		usleep_range(1000, 2000);
		*data = readl(scu->i2c_base + I2C_DATA_ADDR);
	} else if (cmd == IPC_I2C_WRITE) {
		writel(*data, scu->i2c_base + I2C_DATA_ADDR);
		usleep_range(1000, 2000);
		writel(addr, scu->i2c_base + IPC_I2C_CNTRL_ADDR);
	} else {
		dev_err(scu->dev,
			"intel_scu_ipc: I2C INVALID_CMD = 0x%x\n", cmd);

		mutex_unlock(&ipclock);
		return -EIO;
	}
	mutex_unlock(&ipclock);
	return 0;
}