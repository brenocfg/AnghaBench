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
struct ionic_intr_info {unsigned long index; } ;
struct ionic_dev {int /*<<< orphan*/  intr_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ionic_intr_clean (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void ionic_intr_init(struct ionic_dev *idev,
				   struct ionic_intr_info *intr,
				   unsigned long index)
{
	ionic_intr_clean(idev->intr_ctrl, index);
	intr->index = index;
}