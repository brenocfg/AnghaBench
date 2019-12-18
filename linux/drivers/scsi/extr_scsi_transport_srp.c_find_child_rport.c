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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (struct device*) ; 
 scalar_t__ scsi_is_srp_rport (struct device*) ; 

__attribute__((used)) static int find_child_rport(struct device *dev, void *data)
{
	struct device **child = data;

	if (scsi_is_srp_rport(dev)) {
		WARN_ON_ONCE(*child);
		*child = dev;
	}
	return 0;
}