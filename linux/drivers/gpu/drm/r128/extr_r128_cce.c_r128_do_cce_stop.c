#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cce_running; } ;
typedef  TYPE_1__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  R128_PM4_BUFFER_CNTL ; 
 int R128_PM4_BUFFER_CNTL_NOUPDATE ; 
 int /*<<< orphan*/  R128_PM4_MICRO_CNTL ; 
 int R128_PM4_NONPM4 ; 
 int /*<<< orphan*/  R128_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r128_do_cce_stop(drm_r128_private_t *dev_priv)
{
	R128_WRITE(R128_PM4_MICRO_CNTL, 0);
	R128_WRITE(R128_PM4_BUFFER_CNTL,
		   R128_PM4_NONPM4 | R128_PM4_BUFFER_CNTL_NOUPDATE);

	dev_priv->cce_running = 0;
}