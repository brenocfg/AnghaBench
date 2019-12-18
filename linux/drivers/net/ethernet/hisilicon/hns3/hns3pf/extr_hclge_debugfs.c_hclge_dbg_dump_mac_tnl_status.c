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
struct hclge_mac_tnl_stats {int /*<<< orphan*/  status; scalar_t__ time; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  mac_tnl_log; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_BILLION_NANO_SECONDS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 unsigned long do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kfifo_get (int /*<<< orphan*/ *,struct hclge_mac_tnl_stats*) ; 

__attribute__((used)) static void hclge_dbg_dump_mac_tnl_status(struct hclge_dev *hdev)
{
#define HCLGE_BILLION_NANO_SECONDS 1000000000

	struct hclge_mac_tnl_stats stats;
	unsigned long rem_nsec;

	dev_info(&hdev->pdev->dev, "Recently generated mac tnl interruption:\n");

	while (kfifo_get(&hdev->mac_tnl_log, &stats)) {
		rem_nsec = do_div(stats.time, HCLGE_BILLION_NANO_SECONDS);
		dev_info(&hdev->pdev->dev, "[%07lu.%03lu] status = 0x%x\n",
			 (unsigned long)stats.time, rem_nsec / 1000,
			 stats.status);
	}
}