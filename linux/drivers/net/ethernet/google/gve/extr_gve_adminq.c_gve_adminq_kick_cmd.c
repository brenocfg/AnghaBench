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
typedef  int /*<<< orphan*/  u32 ;
struct gve_priv {TYPE_1__* reg_bar0; } ;
struct TYPE_2__ {int /*<<< orphan*/  adminq_doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gve_adminq_kick_cmd(struct gve_priv *priv, u32 prod_cnt)
{
	iowrite32be(prod_cnt, &priv->reg_bar0->adminq_doorbell);
}