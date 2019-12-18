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
struct mbo {int dummy; } ;
struct comp_channel {int /*<<< orphan*/  fifo; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 TYPE_1__ comp ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,struct mbo**,int) ; 
 int /*<<< orphan*/  kfifo_peek (int /*<<< orphan*/ *,struct mbo**) ; 
 struct mbo* most_get_mbo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct mbo *ch_get_mbo(struct comp_channel *c, struct mbo **mbo)
{
	if (!kfifo_peek(&c->fifo, mbo)) {
		*mbo = most_get_mbo(c->iface, c->channel_id, &comp.cc);
		if (*mbo)
			kfifo_in(&c->fifo, mbo, 1);
	}
	return *mbo;
}