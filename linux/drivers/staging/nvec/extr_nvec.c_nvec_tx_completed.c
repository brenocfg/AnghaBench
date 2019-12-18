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
struct nvec_chip {scalar_t__ state; TYPE_1__* tx; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ pos; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvec_gpio_set_value (struct nvec_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvec_tx_completed(struct nvec_chip *nvec)
{
	/* We got an END_TRANS, let's skip this, maybe there's an event */
	if (nvec->tx->pos != nvec->tx->size) {
		dev_err(nvec->dev, "premature END_TRANS, resending\n");
		nvec->tx->pos = 0;
		nvec_gpio_set_value(nvec, 0);
	} else {
		nvec->state = 0;
	}
}