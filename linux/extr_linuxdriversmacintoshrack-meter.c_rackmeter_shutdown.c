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
struct rackmeter {int /*<<< orphan*/  dma_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct macio_dev {TYPE_1__ ofdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBDMA_DO_RESET (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 struct rackmeter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rackmeter_stop_cpu_sniffer (struct rackmeter*) ; 

__attribute__((used)) static int rackmeter_shutdown(struct macio_dev* mdev)
{
	struct rackmeter *rm = dev_get_drvdata(&mdev->ofdev.dev);

	if (rm == NULL)
		return -ENODEV;

	/* Stop CPU sniffer timer & work queues */
	rackmeter_stop_cpu_sniffer(rm);

	/* Stop/reset dbdma */
	DBDMA_DO_RESET(rm->dma_regs);

	return 0;
}