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
struct scif_window {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  rma_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  scif_queue_for_cleanup (struct scif_window*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __scif_rma_destroy_tcw_helper(struct scif_window *window)
{
	list_del_init(&window->list);
	scif_queue_for_cleanup(window, &scif_info.rma_tc);
}