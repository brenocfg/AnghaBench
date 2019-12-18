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
struct mt76x02_dev {int /*<<< orphan*/  ed_monitor_enabled; } ;

/* Variables and functions */

__attribute__((used)) static int
mt76_edcca_get(void *data, u64 *val)
{
	struct mt76x02_dev *dev = data;

	*val = dev->ed_monitor_enabled;
	return 0;
}