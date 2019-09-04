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
struct csiphy_device {int /*<<< orphan*/  cfg; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lanes_disable ) (struct csiphy_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct csiphy_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void csiphy_stream_off(struct csiphy_device *csiphy)
{
	csiphy->ops->lanes_disable(csiphy, &csiphy->cfg);
}