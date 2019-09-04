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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_CMD_CTL ; 
 int PTP_CMD_CTL_PTP_ENABLE_ ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool lan743x_ptp_is_enabled(struct lan743x_adapter *adapter)
{
	if (lan743x_csr_read(adapter, PTP_CMD_CTL) & PTP_CMD_CTL_PTP_ENABLE_)
		return true;
	return false;
}