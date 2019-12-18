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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct ksz_device {int /*<<< orphan*/  alu_mutex; } ;

/* Variables and functions */
 int IND_ACC_TABLE (int) ; 
 int /*<<< orphan*/  REG_IND_CTRL_0 ; 
 int /*<<< orphan*/  REG_IND_DATA_HI ; 
 int TABLE_READ ; 
 int /*<<< orphan*/  ksz_read64 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_write16 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz8795_r_table(struct ksz_device *dev, int table, u16 addr,
			    u64 *data)
{
	u16 ctrl_addr;

	ctrl_addr = IND_ACC_TABLE(table | TABLE_READ) | addr;

	mutex_lock(&dev->alu_mutex);
	ksz_write16(dev, REG_IND_CTRL_0, ctrl_addr);
	ksz_read64(dev, REG_IND_DATA_HI, data);
	mutex_unlock(&dev->alu_mutex);
}