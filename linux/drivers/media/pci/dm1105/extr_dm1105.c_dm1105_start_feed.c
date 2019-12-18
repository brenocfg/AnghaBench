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
struct dvb_demux_feed {int dummy; } ;
struct dm1105_dev {int /*<<< orphan*/  full_ts_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm1105_enable_irqs (struct dm1105_dev*) ; 
 struct dm1105_dev* feed_to_dm1105_dev (struct dvb_demux_feed*) ; 

__attribute__((used)) static int dm1105_start_feed(struct dvb_demux_feed *f)
{
	struct dm1105_dev *dev = feed_to_dm1105_dev(f);

	if (dev->full_ts_users++ == 0)
		dm1105_enable_irqs(dev);

	return 0;
}