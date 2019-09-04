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
struct vpss_sync_pol {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_sync_pol ) (struct vpss_sync_pol) ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 TYPE_2__ oper_cfg ; 
 int /*<<< orphan*/  stub1 (struct vpss_sync_pol) ; 

void vpss_set_sync_pol(struct vpss_sync_pol sync)
{
	if (!oper_cfg.hw_ops.set_sync_pol)
		return;

	oper_cfg.hw_ops.set_sync_pol(sync);
}