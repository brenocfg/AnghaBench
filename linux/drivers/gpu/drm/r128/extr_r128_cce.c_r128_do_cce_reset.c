#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tail; } ;
struct TYPE_5__ {TYPE_1__ ring; } ;
typedef  TYPE_2__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  R128_PM4_BUFFER_DL_RPTR ; 
 int /*<<< orphan*/  R128_PM4_BUFFER_DL_WPTR ; 
 int /*<<< orphan*/  R128_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r128_do_cce_reset(drm_r128_private_t *dev_priv)
{
	R128_WRITE(R128_PM4_BUFFER_DL_WPTR, 0);
	R128_WRITE(R128_PM4_BUFFER_DL_RPTR, 0);
	dev_priv->ring.tail = 0;
}