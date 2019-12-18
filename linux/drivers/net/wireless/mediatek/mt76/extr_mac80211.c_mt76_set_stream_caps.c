#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sband; } ;
struct TYPE_5__ {scalar_t__ has_5ghz; scalar_t__ has_2ghz; } ;
struct TYPE_4__ {int /*<<< orphan*/  sband; } ;
struct mt76_dev {TYPE_3__ sband_5g; TYPE_2__ cap; TYPE_1__ sband_2g; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_init_stream_cap (struct mt76_dev*,int /*<<< orphan*/ *,int) ; 

void mt76_set_stream_caps(struct mt76_dev *dev, bool vht)
{
	if (dev->cap.has_2ghz)
		mt76_init_stream_cap(dev, &dev->sband_2g.sband, false);
	if (dev->cap.has_5ghz)
		mt76_init_stream_cap(dev, &dev->sband_5g.sband, vht);
}