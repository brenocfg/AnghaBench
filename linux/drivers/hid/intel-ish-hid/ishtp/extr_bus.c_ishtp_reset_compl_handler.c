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
struct ishtp_device {int /*<<< orphan*/  hbm_state; int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISHTP_DEV_INIT_CLIENTS ; 
 int /*<<< orphan*/  ISHTP_HBM_START ; 
 int /*<<< orphan*/  ishtp_hbm_start_req (struct ishtp_device*) ; 

void ishtp_reset_compl_handler(struct ishtp_device *dev)
{
	dev->dev_state = ISHTP_DEV_INIT_CLIENTS;
	dev->hbm_state = ISHTP_HBM_START;
	ishtp_hbm_start_req(dev);
}