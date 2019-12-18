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
struct wd719x {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WD719X_AMR_COMMAND ; 
 scalar_t__ WD719X_CMD_READY ; 
 int /*<<< orphan*/  WD719X_WAIT_FOR_CMD_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wd719x_readb (struct wd719x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wd719x_wait_ready(struct wd719x *wd)
{
	int i = 0;

	do {
		if (wd719x_readb(wd, WD719X_AMR_COMMAND) == WD719X_CMD_READY)
			return 0;
		udelay(1);
	} while (i++ < WD719X_WAIT_FOR_CMD_READY);

	dev_err(&wd->pdev->dev, "command register is not ready: 0x%02x\n",
		wd719x_readb(wd, WD719X_AMR_COMMAND));

	return -ETIMEDOUT;
}