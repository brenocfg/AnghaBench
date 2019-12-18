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
struct TYPE_2__ {int /*<<< orphan*/  db_bar; } ;
struct efa_dev {TYPE_1__ dev_attr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EFA_BASE_BAR_MASK ; 
 int /*<<< orphan*/  efa_release_bars (struct efa_dev*,int) ; 

__attribute__((used)) static void efa_release_doorbell_bar(struct efa_dev *dev)
{
	if (!(BIT(dev->dev_attr.db_bar) & EFA_BASE_BAR_MASK))
		efa_release_bars(dev, BIT(dev->dev_attr.db_bar));
}