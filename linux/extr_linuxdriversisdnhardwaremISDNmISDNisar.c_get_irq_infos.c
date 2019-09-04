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
struct isar_hw {int /*<<< orphan*/  clsb; int /*<<< orphan*/  cmsb; int /*<<< orphan*/  iis; int /*<<< orphan*/  name; int /*<<< orphan*/  hw; int /*<<< orphan*/  (* read_reg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISAR_CTRL_H ; 
 int /*<<< orphan*/  ISAR_CTRL_L ; 
 int /*<<< orphan*/  ISAR_IIS ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
get_irq_infos(struct isar_hw *isar)
{
	isar->iis = isar->read_reg(isar->hw, ISAR_IIS);
	isar->cmsb = isar->read_reg(isar->hw, ISAR_CTRL_H);
	isar->clsb = isar->read_reg(isar->hw, ISAR_CTRL_L);
	pr_debug("%s: rcv_mbox(%02x,%02x,%d)\n", isar->name,
		 isar->iis, isar->cmsb, isar->clsb);
}