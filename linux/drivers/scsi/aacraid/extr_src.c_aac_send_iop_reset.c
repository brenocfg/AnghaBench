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
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  IDR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP_SRC_RESET_MASK ; 
 TYPE_1__ MUnit ; 
 int /*<<< orphan*/  aac_clear_omr (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_dump_fw_fib_iop_reset (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_notify_fw_of_iop_reset (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_set_intx_mode (struct aac_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  src_writel (struct aac_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aac_send_iop_reset(struct aac_dev *dev)
{
	aac_dump_fw_fib_iop_reset(dev);

	aac_notify_fw_of_iop_reset(dev);

	aac_set_intx_mode(dev);

	aac_clear_omr(dev);

	src_writel(dev, MUnit.IDR, IOP_SRC_RESET_MASK);

	msleep(5000);
}