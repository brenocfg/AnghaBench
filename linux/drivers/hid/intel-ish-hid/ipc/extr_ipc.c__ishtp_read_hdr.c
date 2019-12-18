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
 int /*<<< orphan*/  IPC_REG_ISH2HOST_MSG ; 
 int /*<<< orphan*/  ish_reg_read (struct ishtp_device const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t _ishtp_read_hdr(const struct ishtp_device *dev)
{
	return ish_reg_read(dev, IPC_REG_ISH2HOST_MSG);
}