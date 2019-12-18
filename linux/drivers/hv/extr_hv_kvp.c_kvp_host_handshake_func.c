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
struct work_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__* recv_channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  callback_event; } ;

/* Variables and functions */
 TYPE_2__ kvp_transaction ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvp_host_handshake_func(struct work_struct *dummy)
{
	tasklet_schedule(&kvp_transaction.recv_channel->callback_event);
}