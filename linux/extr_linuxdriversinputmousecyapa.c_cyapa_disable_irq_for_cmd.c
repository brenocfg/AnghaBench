#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int /*<<< orphan*/  users; } ;
struct cyapa {scalar_t__ gen; TYPE_2__* ops; scalar_t__ operational; TYPE_1__* client; struct input_dev* input; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_power_mode ) (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ CYAPA_GEN5 ; 
 int /*<<< orphan*/  CYAPA_PM_ACTIVE ; 
 int /*<<< orphan*/  PWR_MODE_OFF ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyapa_disable_irq_for_cmd(struct cyapa *cyapa)
{
	struct input_dev *input = cyapa->input;

	if (!input || !input->users) {
		if (cyapa->gen >= CYAPA_GEN5)
			disable_irq(cyapa->client->irq);
		if (!input || cyapa->operational)
			cyapa->ops->set_power_mode(cyapa,
					PWR_MODE_OFF, 0, CYAPA_PM_ACTIVE);
	}
}