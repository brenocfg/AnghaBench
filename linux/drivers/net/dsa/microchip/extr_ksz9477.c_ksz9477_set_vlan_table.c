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
typedef  void* u32 ;
typedef  size_t u16 ;
struct ksz_device {int /*<<< orphan*/  vlan_mutex; TYPE_1__* vlan_cache; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void** table; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SW_VLAN_CTRL ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY_INDEX__2 ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY_PORTS__4 ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY_UNTAG__4 ; 
 int /*<<< orphan*/  REG_SW_VLAN_ENTRY__4 ; 
 size_t VLAN_INDEX_M ; 
 int VLAN_START ; 
 int VLAN_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int ksz9477_wait_vlan_ctrl_ready (struct ksz_device*) ; 
 int /*<<< orphan*/  ksz_write16 (struct ksz_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ksz_write32 (struct ksz_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ksz9477_set_vlan_table(struct ksz_device *dev, u16 vid,
				  u32 *vlan_table)
{
	int ret;

	mutex_lock(&dev->vlan_mutex);

	ksz_write32(dev, REG_SW_VLAN_ENTRY__4, vlan_table[0]);
	ksz_write32(dev, REG_SW_VLAN_ENTRY_UNTAG__4, vlan_table[1]);
	ksz_write32(dev, REG_SW_VLAN_ENTRY_PORTS__4, vlan_table[2]);

	ksz_write16(dev, REG_SW_VLAN_ENTRY_INDEX__2, vid & VLAN_INDEX_M);
	ksz_write8(dev, REG_SW_VLAN_CTRL, VLAN_START | VLAN_WRITE);

	/* wait to be cleared */
	ret = ksz9477_wait_vlan_ctrl_ready(dev);
	if (ret) {
		dev_dbg(dev->dev, "Failed to write vlan table\n");
		goto exit;
	}

	ksz_write8(dev, REG_SW_VLAN_CTRL, 0);

	/* update vlan cache table */
	dev->vlan_cache[vid].table[0] = vlan_table[0];
	dev->vlan_cache[vid].table[1] = vlan_table[1];
	dev->vlan_cache[vid].table[2] = vlan_table[2];

exit:
	mutex_unlock(&dev->vlan_mutex);

	return ret;
}