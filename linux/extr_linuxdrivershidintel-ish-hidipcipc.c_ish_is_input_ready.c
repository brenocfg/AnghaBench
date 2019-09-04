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
 int /*<<< orphan*/  IPC_IS_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_REG_HOST2ISH_DRBL ; 
 int /*<<< orphan*/  ish_reg_read (struct ishtp_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ish_is_input_ready(struct ishtp_device *dev)
{
	uint32_t doorbell_val;

	doorbell_val = ish_reg_read(dev, IPC_REG_HOST2ISH_DRBL);
	return !IPC_IS_BUSY(doorbell_val);
}