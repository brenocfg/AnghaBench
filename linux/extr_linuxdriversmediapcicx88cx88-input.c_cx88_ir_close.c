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
struct rc_dev {struct cx88_core* priv; } ;
struct cx88_core {TYPE_1__* ir; } ;
struct TYPE_2__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cx88_ir_stop (struct cx88_core*) ; 

__attribute__((used)) static void cx88_ir_close(struct rc_dev *rc)
{
	struct cx88_core *core = rc->priv;

	core->ir->users--;
	if (!core->ir->users)
		__cx88_ir_stop(core);
}