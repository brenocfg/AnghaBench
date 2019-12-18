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
struct sdricoh_host {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  R21C_STATUS ; 
 int /*<<< orphan*/  R2E4_STATUS_RESP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 unsigned int sdricoh_readl (struct sdricoh_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdricoh_writel (struct sdricoh_host*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sdricoh_query_status(struct sdricoh_host *host, unsigned int wanted,
				unsigned int timeout){
	unsigned int loop;
	unsigned int status = 0;
	struct device *dev = host->dev;
	for (loop = 0; loop < timeout; loop++) {
		status = sdricoh_readl(host, R21C_STATUS);
		sdricoh_writel(host, R2E4_STATUS_RESP, status);
		if (status & wanted)
			break;
	}

	if (loop == timeout) {
		dev_err(dev, "query_status: timeout waiting for %x\n", wanted);
		return -ETIMEDOUT;
	}

	/* do not do this check in the loop as some commands fail otherwise */
	if (status & 0x7F0000) {
		dev_err(dev, "waiting for status bit %x failed\n", wanted);
		return -EINVAL;
	}
	return 0;

}