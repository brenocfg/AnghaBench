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
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct uwb_dev_addr {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct uwb_rc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  uwb_dev_addr_cmp (int /*<<< orphan*/ *,struct uwb_dev_addr const*) ; 
 struct uwb_rc* uwb_rc_get (struct uwb_rc*) ; 

__attribute__((used)) static int find_rc_dev(struct device *dev, const void *data)
{
	const struct uwb_dev_addr *addr = data;
	struct uwb_rc *rc = dev_get_drvdata(dev);

	if (rc == NULL) {
		WARN_ON(1);
		return 0;
	}
	if (!uwb_dev_addr_cmp(&rc->uwb_dev.dev_addr, addr)) {
		rc = uwb_rc_get(rc);
		return 1;
	}
	return 0;
}