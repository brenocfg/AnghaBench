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
struct cdns3 {TYPE_1__* otg_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ien; } ;

/* Variables and functions */
 int OTGIEN_ID_CHANGE_INT ; 
 int OTGIEN_VBUSVALID_FALL_INT ; 
 int OTGIEN_VBUSVALID_RISE_INT ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdns3_otg_enable_irq(struct cdns3 *cdns)
{
	writel(OTGIEN_ID_CHANGE_INT | OTGIEN_VBUSVALID_RISE_INT |
	       OTGIEN_VBUSVALID_FALL_INT, &cdns->otg_regs->ien);
}