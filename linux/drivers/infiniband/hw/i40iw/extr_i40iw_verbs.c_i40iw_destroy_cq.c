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
struct ib_udata {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct i40iw_sc_cq {int dummy; } ;
struct i40iw_device {int dummy; } ;
struct i40iw_cq {struct i40iw_sc_cq sc_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cq_free_resources (struct i40iw_device*,struct i40iw_cq*) ; 
 int /*<<< orphan*/  i40iw_cq_wq_destroy (struct i40iw_device*,struct i40iw_sc_cq*) ; 
 int /*<<< orphan*/  i40iw_rem_devusecount (struct i40iw_device*) ; 
 struct i40iw_cq* to_iwcq (struct ib_cq*) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_destroy_cq(struct ib_cq *ib_cq, struct ib_udata *udata)
{
	struct i40iw_cq *iwcq;
	struct i40iw_device *iwdev;
	struct i40iw_sc_cq *cq;

	iwcq = to_iwcq(ib_cq);
	iwdev = to_iwdev(ib_cq->device);
	cq = &iwcq->sc_cq;
	i40iw_cq_wq_destroy(iwdev, cq);
	cq_free_resources(iwdev, iwcq);
	i40iw_rem_devusecount(iwdev);
}