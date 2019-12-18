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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ksz_device {int /*<<< orphan*/  vlan_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SW_VLAN_CTRL ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY_INDEX__2 ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY_PORTS__4 ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY_UNTAG__4 ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY__4 ; 
 int VLAN_INDEX_M ; 
 int VLAN_READ ; 
 int VLAN_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int ksz9477_wait_vlan_ctrl_ready (struct ksz_device*) ; 
 int /*<<< orphan*/  ksz_read32 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_write16 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ksz9477_get_vlan_table(struct ksz_device *dev, u16 vid,
				  u32 *vlan_table)
{
	int ret;

	mutex_lock(&dev->vlan_mutex);

	ksz_write16(dev, REG_SW_VLAN_ENTRY_INDEX__2, vid & VLAN_INDEX_M);
	ksz_write8(dev, REG_SW_VLAN_CTRL, VLAN_READ | VLAN_START);

	/* wait to be cleared */
	ret = ksz9477_wait_vlan_ctrl_ready(dev);
	if (ret) {
		dev_dbg(dev->dev, "Failed to read vlan table\n");
		goto exit;
	}

	ksz_read32(dev, REG_SW_VLAN_ENTRY__4, &vlan_table[0]);
	ksz_read32(dev, REG_SW_VLAN_ENTRY_UNTAG__4, &vlan_table[1]);
	ksz_read32(dev, REG_SW_VLAN_ENTRY_PORTS__4, &vlan_table[2]);

	ksz_write8(dev, REG_SW_VLAN_CTRL, 0);

exit:
	mutex_unlock(&dev->vlan_mutex);

	return ret;
}