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
struct sh_msiof_spi_priv {TYPE_1__* pdev; scalar_t__ slave_aborted; int /*<<< orphan*/  ctlr; } ;
struct completion {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ spi_controller_is_slave (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_interruptible (struct completion*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_msiof_wait_for_completion(struct sh_msiof_spi_priv *p,
					struct completion *x)
{
	if (spi_controller_is_slave(p->ctlr)) {
		if (wait_for_completion_interruptible(x) ||
		    p->slave_aborted) {
			dev_dbg(&p->pdev->dev, "interrupted\n");
			return -EINTR;
		}
	} else {
		if (!wait_for_completion_timeout(x, HZ)) {
			dev_err(&p->pdev->dev, "timeout\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}