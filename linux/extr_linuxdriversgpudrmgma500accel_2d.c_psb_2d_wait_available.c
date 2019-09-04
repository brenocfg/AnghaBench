#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int uint32_t ;
struct drm_psb_private {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  PSB_CR_2D_SOCIF ; 
 unsigned int PSB_RSGX32 (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  psb_spank (struct drm_psb_private*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int psb_2d_wait_available(struct drm_psb_private *dev_priv,
			  unsigned size)
{
	uint32_t avail = PSB_RSGX32(PSB_CR_2D_SOCIF);
	unsigned long t = jiffies + HZ;

	while (avail < size) {
		avail = PSB_RSGX32(PSB_CR_2D_SOCIF);
		if (time_after(jiffies, t)) {
			psb_spank(dev_priv);
			return -EIO;
		}
	}
	return 0;
}