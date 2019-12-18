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
struct xenvif {unsigned int num_queues; int /*<<< orphan*/ * queues; } ;
struct backend_info {struct xenvif* vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_unregister_watchers (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_debugfs_delif (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_deinit_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenvif_disconnect_ctrl (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_disconnect_data (struct xenvif*) ; 

__attribute__((used)) static void backend_disconnect(struct backend_info *be)
{
	struct xenvif *vif = be->vif;

	if (vif) {
		unsigned int num_queues = vif->num_queues;
		unsigned int queue_index;

		xen_unregister_watchers(vif);
#ifdef CONFIG_DEBUG_FS
		xenvif_debugfs_delif(vif);
#endif /* CONFIG_DEBUG_FS */
		xenvif_disconnect_data(vif);

		/* At this point some of the handlers may still be active
		 * so we need to have additional synchronization here.
		 */
		vif->num_queues = 0;
		synchronize_net();

		for (queue_index = 0; queue_index < num_queues; ++queue_index)
			xenvif_deinit_queue(&vif->queues[queue_index]);

		vfree(vif->queues);
		vif->queues = NULL;

		xenvif_disconnect_ctrl(vif);
	}
}