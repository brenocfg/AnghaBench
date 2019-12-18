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
struct ath10k_bus_params {int dummy; } ;
struct ath10k {int /*<<< orphan*/  register_work; int /*<<< orphan*/  workqueue; struct ath10k_bus_params bus_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ath10k_core_register(struct ath10k *ar,
			 const struct ath10k_bus_params *bus_params)
{
	ar->bus_param = *bus_params;

	queue_work(ar->workqueue, &ar->register_work);

	return 0;
}