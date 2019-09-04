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
typedef  scalar_t__ uint64_t ;
typedef  int u32 ;
struct ksz_device {int /*<<< orphan*/  stats_mutex; scalar_t__* mib_value; int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct ksz_device* priv; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int MIB_COUNTER_INDEX_S ; 
 int MIB_COUNTER_READ ; 
 int /*<<< orphan*/  REG_PORT_MIB_CTRL_STAT__4 ; 
 int /*<<< orphan*/  REG_PORT_MIB_DATA ; 
 int TOTAL_SWITCH_COUNTER_NUM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ksz_pread32 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_pwrite32 (struct ksz_device*,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mib_names ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ksz_get_ethtool_stats(struct dsa_switch *ds, int port,
				  uint64_t *buf)
{
	struct ksz_device *dev = ds->priv;
	int i;
	u32 data;
	int timeout;

	mutex_lock(&dev->stats_mutex);

	for (i = 0; i < TOTAL_SWITCH_COUNTER_NUM; i++) {
		data = MIB_COUNTER_READ;
		data |= ((mib_names[i].index & 0xFF) << MIB_COUNTER_INDEX_S);
		ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4, data);

		timeout = 1000;
		do {
			ksz_pread32(dev, port, REG_PORT_MIB_CTRL_STAT__4,
				    &data);
			usleep_range(1, 10);
			if (!(data & MIB_COUNTER_READ))
				break;
		} while (timeout-- > 0);

		/* failed to read MIB. get out of loop */
		if (!timeout) {
			dev_dbg(dev->dev, "Failed to get MIB\n");
			break;
		}

		/* count resets upon read */
		ksz_pread32(dev, port, REG_PORT_MIB_DATA, &data);

		dev->mib_value[i] += (uint64_t)data;
		buf[i] = dev->mib_value[i];
	}

	mutex_unlock(&dev->stats_mutex);
}