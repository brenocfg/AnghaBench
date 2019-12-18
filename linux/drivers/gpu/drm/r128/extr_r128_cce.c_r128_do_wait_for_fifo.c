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
struct TYPE_3__ {int usec_timeout; } ;
typedef  TYPE_1__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EBUSY ; 
 int R128_GUI_FIFOCNT_MASK ; 
 int /*<<< orphan*/  R128_GUI_STAT ; 
 int R128_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int r128_do_wait_for_fifo(drm_r128_private_t *dev_priv, int entries)
{
	int i;

	for (i = 0; i < dev_priv->usec_timeout; i++) {
		int slots = R128_READ(R128_GUI_STAT) & R128_GUI_FIFOCNT_MASK;
		if (slots >= entries)
			return 0;
		udelay(1);
	}

#if R128_FIFO_DEBUG
	DRM_ERROR("failed!\n");
#endif
	return -EBUSY;
}