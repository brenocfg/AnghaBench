#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  line; int /*<<< orphan*/  filename_0_7; } ;
struct TYPE_3__ {TYPE_2__ assert; } ;
struct fw_debug_cmd {TYPE_1__ u; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; } ;
typedef  int /*<<< orphan*/  asrt ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mbox_rpl (struct adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fw_asrt(struct adapter *adap, u32 mbox_addr)
{
	struct fw_debug_cmd asrt;

	get_mbox_rpl(adap, (__be64 *)&asrt, sizeof(asrt) / 8, mbox_addr);
	dev_alert(adap->pdev_dev,
		  "FW assertion at %.16s:%u, val0 %#x, val1 %#x\n",
		  asrt.u.assert.filename_0_7, be32_to_cpu(asrt.u.assert.line),
		  be32_to_cpu(asrt.u.assert.x), be32_to_cpu(asrt.u.assert.y));
}