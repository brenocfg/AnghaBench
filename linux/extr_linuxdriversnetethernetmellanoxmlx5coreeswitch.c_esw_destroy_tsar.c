#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int enabled; int /*<<< orphan*/  root_tsar_id; } ;
struct mlx5_eswitch {TYPE_1__ qos; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEDULING_HIERARCHY_E_SWITCH ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int) ; 
 int mlx5_destroy_scheduling_element_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esw_destroy_tsar(struct mlx5_eswitch *esw)
{
	int err;

	if (!esw->qos.enabled)
		return;

	err = mlx5_destroy_scheduling_element_cmd(esw->dev,
						  SCHEDULING_HIERARCHY_E_SWITCH,
						  esw->qos.root_tsar_id);
	if (err)
		esw_warn(esw->dev, "E-Switch destroy TSAR failed (%d)\n", err);

	esw->qos.enabled = false;
}