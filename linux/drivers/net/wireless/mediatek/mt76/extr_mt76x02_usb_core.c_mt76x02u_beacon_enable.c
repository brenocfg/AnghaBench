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
struct TYPE_2__ {int /*<<< orphan*/  beacon_int; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int N_BCN_SLOTS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mt76x02_mac_set_beacon (struct mt76x02_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02u_start_pre_tbtt_timer (struct mt76x02_dev*) ; 

__attribute__((used)) static void mt76x02u_beacon_enable(struct mt76x02_dev *dev, bool en)
{
	int i;

	if (WARN_ON_ONCE(!dev->mt76.beacon_int))
		return;

	if (en) {
		mt76x02u_start_pre_tbtt_timer(dev);
	} else {
		/* Timer is already stopped, only clean up
		 * PS buffered frames if any.
		 */
		for (i = 0; i < N_BCN_SLOTS; i++)
			mt76x02_mac_set_beacon(dev, i, NULL);
	}
}