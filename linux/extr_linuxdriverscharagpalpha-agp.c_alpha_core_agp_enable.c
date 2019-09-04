#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct agp_bridge_data {TYPE_5__* dev_private_data; } ;
struct TYPE_8__ {int enable; } ;
struct TYPE_9__ {int /*<<< orphan*/  lw; TYPE_2__ bits; } ;
struct TYPE_7__ {int /*<<< orphan*/  lw; } ;
struct TYPE_11__ {TYPE_3__ mode; TYPE_4__* ops; TYPE_1__ capability; } ;
typedef  TYPE_5__ alpha_agp_info ;
struct TYPE_10__ {int /*<<< orphan*/  (* configure ) (TYPE_5__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  agp_collect_device_status (struct agp_bridge_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_device_command (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static void alpha_core_agp_enable(struct agp_bridge_data *bridge, u32 mode)
{
	alpha_agp_info *agp = bridge->dev_private_data;

	agp->mode.lw = agp_collect_device_status(bridge, mode,
					agp->capability.lw);

	agp->mode.bits.enable = 1;
	agp->ops->configure(agp);

	agp_device_command(agp->mode.lw, false);
}