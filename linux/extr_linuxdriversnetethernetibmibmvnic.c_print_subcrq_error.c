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
#define  H_CLOSED 129 
#define  H_PARAMETER 128 
 int /*<<< orphan*/  dev_err_ratelimited (struct device*,char*,char const*,int) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (struct device*,char*,char const*,int) ; 

__attribute__((used)) static void print_subcrq_error(struct device *dev, int rc, const char *func)
{
	switch (rc) {
	case H_PARAMETER:
		dev_warn_ratelimited(dev,
				     "%s failed: Send request is malformed or adapter failover pending. (rc=%d)\n",
				     func, rc);
		break;
	case H_CLOSED:
		dev_warn_ratelimited(dev,
				     "%s failed: Backing queue closed. Adapter is down or failover pending. (rc=%d)\n",
				     func, rc);
		break;
	default:
		dev_err_ratelimited(dev, "%s failed: (rc=%d)\n", func, rc);
		break;
	}
}