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
struct mei_device {int /*<<< orphan*/  hbm_state; scalar_t__ init_clients_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_HBM_IDLE ; 

void mei_hbm_idle(struct mei_device *dev)
{
	dev->init_clients_timer = 0;
	dev->hbm_state = MEI_HBM_IDLE;
}