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
 int /*<<< orphan*/  mt76_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76_reg_get(void *data, u64 *val)
{
	struct mt7601u_dev *dev = data;

	*val = mt76_rr(dev, dev->debugfs_reg);
	return 0;
}