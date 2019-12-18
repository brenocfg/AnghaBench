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
typedef  int /*<<< orphan*/  u32 ;
struct mt76x02_dev {int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_INT_MASK_CSR ; 
 int /*<<< orphan*/  mt76_set_irq_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mt76x02_irq_disable(struct mt76x02_dev *dev, u32 mask)
{
	mt76_set_irq_mask(&dev->mt76, MT_INT_MASK_CSR, mask, 0);
}