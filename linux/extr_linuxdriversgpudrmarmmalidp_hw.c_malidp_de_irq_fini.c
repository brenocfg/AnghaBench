#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct malidp_hw_device {TYPE_4__* hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq_mask; } ;
struct TYPE_7__ {TYPE_2__ dc_irq_map; TYPE_1__ de_irq_map; } ;
struct TYPE_8__ {TYPE_3__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALIDP_DC_BLOCK ; 
 int /*<<< orphan*/  MALIDP_DE_BLOCK ; 
 int /*<<< orphan*/  malidp_hw_disable_irq (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void malidp_de_irq_fini(struct malidp_hw_device *hwdev)
{
	malidp_hw_disable_irq(hwdev, MALIDP_DE_BLOCK,
			      hwdev->hw->map.de_irq_map.irq_mask);
	malidp_hw_disable_irq(hwdev, MALIDP_DC_BLOCK,
			      hwdev->hw->map.dc_irq_map.irq_mask);
}