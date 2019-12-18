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
struct i40iw_sc_dev {scalar_t__ back_dev; } ;
struct i40iw_sc_cq {int dummy; } ;
struct i40iw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_cq_wq_destroy (struct i40iw_device*,struct i40iw_sc_cq*) ; 

void i40iw_cqp_cq_destroy_cmd(struct i40iw_sc_dev *dev, struct i40iw_sc_cq *cq)
{
	struct i40iw_device *iwdev = (struct i40iw_device *)dev->back_dev;

	i40iw_cq_wq_destroy(iwdev, cq);
}