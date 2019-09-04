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
struct vc_dmaman {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dmaman_dev ; 
 struct vc_dmaman* g_dmaman ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vc_dmaman_chan_free (struct vc_dmaman*,int) ; 

extern int bcm_dma_chan_free(int channel)
{
	struct vc_dmaman *dmaman = g_dmaman;
	int rc;

	if (!dmaman_dev)
		return -ENODEV;

	mutex_lock(&dmaman->lock);
	rc = vc_dmaman_chan_free(dmaman, channel);
	mutex_unlock(&dmaman->lock);

	return rc;
}