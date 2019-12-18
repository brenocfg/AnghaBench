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
struct rt2x00_dev {int /*<<< orphan*/  pretbtt_tasklet; int /*<<< orphan*/  tbtt_tasklet; } ;
struct data_queue {int qid; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_TIME_CFG ; 
 int /*<<< orphan*/  BCN_TIME_CFG_BEACON_GEN ; 
 int /*<<< orphan*/  BCN_TIME_CFG_TBTT_ENABLE ; 
 int /*<<< orphan*/  BCN_TIME_CFG_TSF_TICKING ; 
 int /*<<< orphan*/  INT_TIMER_EN ; 
 int /*<<< orphan*/  INT_TIMER_EN_PRE_TBTT_TIMER ; 
 int /*<<< orphan*/  MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_ENABLE_RX ; 
#define  QID_BEACON 129 
#define  QID_RX 128 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void rt2800mmio_stop_queue(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	switch (queue->qid) {
	case QID_RX:
		reg = rt2x00mmio_register_read(rt2x00dev, MAC_SYS_CTRL);
		rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
		rt2x00mmio_register_write(rt2x00dev, MAC_SYS_CTRL, reg);
		break;
	case QID_BEACON:
		reg = rt2x00mmio_register_read(rt2x00dev, BCN_TIME_CFG);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_TICKING, 0);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TBTT_ENABLE, 0);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
		rt2x00mmio_register_write(rt2x00dev, BCN_TIME_CFG, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, INT_TIMER_EN);
		rt2x00_set_field32(&reg, INT_TIMER_EN_PRE_TBTT_TIMER, 0);
		rt2x00mmio_register_write(rt2x00dev, INT_TIMER_EN, reg);

		/*
		 * Wait for current invocation to finish. The tasklet
		 * won't be scheduled anymore afterwards since we disabled
		 * the TBTT and PRE TBTT timer.
		 */
		tasklet_kill(&rt2x00dev->tbtt_tasklet);
		tasklet_kill(&rt2x00dev->pretbtt_tasklet);

		break;
	default:
		break;
	}
}