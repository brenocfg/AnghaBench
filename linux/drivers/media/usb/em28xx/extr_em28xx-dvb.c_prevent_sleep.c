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
struct TYPE_2__ {int /*<<< orphan*/ * sleep; } ;
struct dvb_frontend_ops {TYPE_1__ tuner_ops; int /*<<< orphan*/ * sleep; int /*<<< orphan*/ * set_voltage; } ;

/* Variables and functions */

__attribute__((used)) static inline void prevent_sleep(struct dvb_frontend_ops *ops)
{
	ops->set_voltage = NULL;
	ops->sleep = NULL;
	ops->tuner_ops.sleep = NULL;
}