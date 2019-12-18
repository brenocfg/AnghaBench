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
struct fotg210_hcd {unsigned int uframe_periodic_max; unsigned int periodic_size; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fotg210_info (struct fotg210_hcd*,char*,int,...) ; 
 int /*<<< orphan*/  fotg210_warn (struct fotg210_hcd*,char*) ; 
 struct fotg210_hcd* hcd_to_fotg210 (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned short max (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periodic_usecs (struct fotg210_hcd*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t uframe_periodic_max_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct fotg210_hcd *fotg210;
	unsigned uframe_periodic_max;
	unsigned frame, uframe;
	unsigned short allocated_max;
	unsigned long flags;
	ssize_t ret;

	fotg210 = hcd_to_fotg210(bus_to_hcd(dev_get_drvdata(dev)));
	if (kstrtouint(buf, 0, &uframe_periodic_max) < 0)
		return -EINVAL;

	if (uframe_periodic_max < 100 || uframe_periodic_max >= 125) {
		fotg210_info(fotg210, "rejecting invalid request for uframe_periodic_max=%u\n",
				uframe_periodic_max);
		return -EINVAL;
	}

	ret = -EINVAL;

	/*
	 * lock, so that our checking does not race with possible periodic
	 * bandwidth allocation through submitting new urbs.
	 */
	spin_lock_irqsave(&fotg210->lock, flags);

	/*
	 * for request to decrease max periodic bandwidth, we have to check
	 * every microframe in the schedule to see whether the decrease is
	 * possible.
	 */
	if (uframe_periodic_max < fotg210->uframe_periodic_max) {
		allocated_max = 0;

		for (frame = 0; frame < fotg210->periodic_size; ++frame)
			for (uframe = 0; uframe < 7; ++uframe)
				allocated_max = max(allocated_max,
						periodic_usecs(fotg210, frame,
						uframe));

		if (allocated_max > uframe_periodic_max) {
			fotg210_info(fotg210,
					"cannot decrease uframe_periodic_max because periodic bandwidth is already allocated (%u > %u)\n",
					allocated_max, uframe_periodic_max);
			goto out_unlock;
		}
	}

	/* increasing is always ok */

	fotg210_info(fotg210,
			"setting max periodic bandwidth to %u%% (== %u usec/uframe)\n",
			100 * uframe_periodic_max/125, uframe_periodic_max);

	if (uframe_periodic_max != 100)
		fotg210_warn(fotg210, "max periodic bandwidth set is non-standard\n");

	fotg210->uframe_periodic_max = uframe_periodic_max;
	ret = count;

out_unlock:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	return ret;
}