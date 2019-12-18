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
typedef  int u64 ;
struct kp2000_device {int ssid; TYPE_1__* pdev; scalar_t__ sysinfo_regs_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ REG_FPGA_SSID ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int jiffies ; 
 int readq (scalar_t__) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static void wait_and_read_ssid(struct kp2000_device *pcard)
{
	u64 read_val = readq(pcard->sysinfo_regs_base + REG_FPGA_SSID);
	unsigned long timeout;

	if (read_val & 0x8000000000000000UL) {
		pcard->ssid = read_val;
		return;
	}

	timeout = jiffies + (HZ * 2);
	do {
		read_val = readq(pcard->sysinfo_regs_base + REG_FPGA_SSID);
		if (read_val & 0x8000000000000000UL) {
			pcard->ssid = read_val;
			return;
		}
		cpu_relax();
		//schedule();
	} while (time_before(jiffies, timeout));

	dev_notice(&pcard->pdev->dev, "SSID didn't show up!\n");

	// Timed out waiting for the SSID to show up, stick all zeros in the
	// value
	pcard->ssid = 0;
}