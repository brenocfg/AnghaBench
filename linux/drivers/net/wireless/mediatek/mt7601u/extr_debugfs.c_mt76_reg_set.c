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
struct mt7601u_dev {int /*<<< orphan*/  debugfs_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76_reg_set(void *data, u64 val)
{
	struct mt7601u_dev *dev = data;

	mt76_wr(dev, dev->debugfs_reg, val);
	return 0;
}