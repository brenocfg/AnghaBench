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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  stage; } ;
struct fmdev {TYPE_1__ irq_info; } ;

/* Variables and functions */
 scalar_t__ FM_DRV_TX_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void fm_irq_timeout_stage(struct fmdev *fmdev, u8 stage)
{
	fmdev->irq_info.stage = stage;
	mod_timer(&fmdev->irq_info.timer, jiffies + FM_DRV_TX_TIMEOUT);
}