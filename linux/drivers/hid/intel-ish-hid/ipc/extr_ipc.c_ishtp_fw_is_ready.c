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
typedef  int /*<<< orphan*/  uint32_t ;
struct ishtp_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPC_IS_ISH_ILUP (int /*<<< orphan*/ ) ; 
 scalar_t__ IPC_IS_ISH_ISHTP_READY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ish_read_fw_sts_reg (struct ishtp_device*) ; 

__attribute__((used)) static bool ishtp_fw_is_ready(struct ishtp_device *dev)
{
	uint32_t ish_status = _ish_read_fw_sts_reg(dev);

	return IPC_IS_ISH_ILUP(ish_status) &&
		IPC_IS_ISH_ISHTP_READY(ish_status);
}