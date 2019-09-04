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
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  provider_data; int /*<<< orphan*/  device; } ;
struct i40iw_device {int /*<<< orphan*/  cm_core; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_cm_del_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 

int i40iw_destroy_listen(struct iw_cm_id *cm_id)
{
	struct i40iw_device *iwdev;

	iwdev = to_iwdev(cm_id->device);
	if (cm_id->provider_data)
		i40iw_cm_del_listen(&iwdev->cm_core, cm_id->provider_data, true);
	else
		i40iw_pr_err("cm_id->provider_data was NULL\n");

	cm_id->rem_ref(cm_id);

	return 0;
}