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
typedef  scalar_t__ u32 ;
struct malidp_hw_device {scalar_t__ regs; int /*<<< orphan*/  pm_suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static inline u32 malidp_hw_read(struct malidp_hw_device *hwdev, u32 reg)
{
	WARN_ON(hwdev->pm_suspended);
	return readl(hwdev->regs + reg);
}