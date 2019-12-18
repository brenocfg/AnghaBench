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
struct TYPE_2__ {int entries; int /*<<< orphan*/ * e; } ;
struct mt7601u_dev {TYPE_1__ rx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int mt7601u_submit_rx_buf (struct mt7601u_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_submit_rx(struct mt7601u_dev *dev)
{
	int i, ret;

	for (i = 0; i < dev->rx_q.entries; i++) {
		ret = mt7601u_submit_rx_buf(dev, &dev->rx_q.e[i], GFP_KERNEL);
		if (ret)
			return ret;
	}

	return 0;
}