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
struct v3d_dev {int /*<<< orphan*/  cache_clean_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_CORE_WRITE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  V3D_CTL_L2TCACTL ; 
 int /*<<< orphan*/  V3D_L2TCACTL_FLM ; 
 int /*<<< orphan*/  V3D_L2TCACTL_FLM_FLUSH ; 
 int V3D_L2TCACTL_L2TFLS ; 
 int V3D_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
v3d_flush_l2t(struct v3d_dev *v3d, int core)
{
	/* While there is a busy bit (V3D_L2TCACTL_L2TFLS), we don't
	 * need to wait for completion before dispatching the job --
	 * L2T accesses will be stalled until the flush has completed.
	 * However, we do need to make sure we don't try to trigger a
	 * new flush while the L2_CLEAN queue is trying to
	 * synchronously clean after a job.
	 */
	mutex_lock(&v3d->cache_clean_lock);
	V3D_CORE_WRITE(core, V3D_CTL_L2TCACTL,
		       V3D_L2TCACTL_L2TFLS |
		       V3D_SET_FIELD(V3D_L2TCACTL_FLM_FLUSH, V3D_L2TCACTL_FLM));
	mutex_unlock(&v3d->cache_clean_lock);
}