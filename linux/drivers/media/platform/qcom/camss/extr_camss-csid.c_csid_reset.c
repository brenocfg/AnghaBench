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
struct csid_device {TYPE_1__* camss; int /*<<< orphan*/  reset_complete; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 scalar_t__ CAMSS_CSID_RST_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSID_RESET_TIMEOUT_MS ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int csid_reset(struct csid_device *csid)
{
	unsigned long time;

	reinit_completion(&csid->reset_complete);

	writel_relaxed(0x7fff, csid->base +
		       CAMSS_CSID_RST_CMD(csid->camss->version));

	time = wait_for_completion_timeout(&csid->reset_complete,
		msecs_to_jiffies(CSID_RESET_TIMEOUT_MS));
	if (!time) {
		dev_err(csid->camss->dev, "CSID reset timeout\n");
		return -EIO;
	}

	return 0;
}