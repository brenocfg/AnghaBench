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
struct mip4_ts {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int mip4_power_on (struct mip4_ts*) ; 

__attribute__((used)) static int mip4_enable(struct mip4_ts *ts)
{
	int error;

	error = mip4_power_on(ts);
	if (error)
		return error;

	enable_irq(ts->client->irq);

	return 0;
}