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
typedef  int /*<<< orphan*/  u32 ;
struct mci {TYPE_1__* base; } ;
struct TYPE_4__ {int device; } ;
struct ddb_link {TYPE_2__ ids; } ;
struct TYPE_3__ {struct ddb_link* link; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SX8_TSCONFIG ; 
 int /*<<< orphan*/  ddblwritel (struct ddb_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ddb_mci_config(struct mci *state, u32 config)
{
	struct ddb_link *link = state->base->link;

	if (link->ids.device != 0x0009)
		return -EINVAL;
	ddblwritel(link, config, SX8_TSCONFIG);
	return 0;
}