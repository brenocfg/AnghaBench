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
struct TYPE_2__ {int /*<<< orphan*/  doorbell; } ;
struct vmballoon {int /*<<< orphan*/  dwork; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_freezable_wq ; 

__attribute__((used)) static void vmballoon_doorbell(void *client_data)
{
	struct vmballoon *b = client_data;

	STATS_INC(b->stats.doorbell);

	mod_delayed_work(system_freezable_wq, &b->dwork, 0);
}