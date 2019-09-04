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
struct gfar_private {int num_grps; TYPE_1__* gfargrp; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enable_napi(struct gfar_private *priv)
{
	int i;

	for (i = 0; i < priv->num_grps; i++) {
		napi_enable(&priv->gfargrp[i].napi_rx);
		napi_enable(&priv->gfargrp[i].napi_tx);
	}
}