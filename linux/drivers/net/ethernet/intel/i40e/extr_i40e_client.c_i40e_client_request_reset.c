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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  pf_id; } ;
struct i40e_pf {TYPE_2__ hw; TYPE_1__* pdev; int /*<<< orphan*/  state; } ;
struct i40e_info {struct i40e_pf* pf; } ;
struct i40e_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  I40E_CLIENT_RESET_LEVEL_CORE 129 
#define  I40E_CLIENT_RESET_LEVEL_PF 128 
 int /*<<< orphan*/  __I40E_PF_RESET_REQUESTED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40e_service_event_schedule (struct i40e_pf*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_client_request_reset(struct i40e_info *ldev,
				      struct i40e_client *client,
				      u32 reset_level)
{
	struct i40e_pf *pf = ldev->pf;

	switch (reset_level) {
	case I40E_CLIENT_RESET_LEVEL_PF:
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		break;
	case I40E_CLIENT_RESET_LEVEL_CORE:
		set_bit(__I40E_PF_RESET_REQUESTED, pf->state);
		break;
	default:
		dev_warn(&pf->pdev->dev,
			 "Client for PF id %d requested an unsupported reset: %d.\n",
			 pf->hw.pf_id, reset_level);
		break;
	}

	i40e_service_event_schedule(pf);
}