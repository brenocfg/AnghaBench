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
struct qp_broker_entry {TYPE_2__* consume_q; TYPE_1__* produce_q; } ;
struct TYPE_4__ {int /*<<< orphan*/ * saved_header; } ;
struct TYPE_3__ {int /*<<< orphan*/ * saved_header; } ;

/* Variables and functions */

__attribute__((used)) static void qp_reset_saved_headers(struct qp_broker_entry *entry)
{
	entry->produce_q->saved_header = NULL;
	entry->consume_q->saved_header = NULL;
}