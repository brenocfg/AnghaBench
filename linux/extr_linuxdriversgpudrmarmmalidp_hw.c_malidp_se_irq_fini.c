#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct malidp_hw_device {TYPE_3__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq_mask; } ;
struct TYPE_5__ {TYPE_1__ se_irq_map; } ;
struct TYPE_6__ {TYPE_2__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALIDP_SE_BLOCK ; 
 int /*<<< orphan*/  malidp_hw_disable_irq (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void malidp_se_irq_fini(struct malidp_hw_device *hwdev)
{
	malidp_hw_disable_irq(hwdev, MALIDP_SE_BLOCK,
			      hwdev->hw->map.se_irq_map.irq_mask);
}