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
struct TYPE_2__ {int /*<<< orphan*/  stage; } ;
struct fmdev {TYPE_1__ irq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm_irq_call (struct fmdev*) ; 

__attribute__((used)) static inline void fm_irq_call_stage(struct fmdev *fmdev, u8 stage)
{
	fmdev->irq_info.stage = stage;
	fm_irq_call(fmdev);
}