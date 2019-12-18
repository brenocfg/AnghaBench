#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_events {int /*<<< orphan*/  nh; } ;

/* Variables and functions */
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,unsigned int,void*) ; 

int mlx5_notifier_call_chain(struct mlx5_events *events, unsigned int event, void *data)
{
	return atomic_notifier_call_chain(&events->nh, event, data);
}