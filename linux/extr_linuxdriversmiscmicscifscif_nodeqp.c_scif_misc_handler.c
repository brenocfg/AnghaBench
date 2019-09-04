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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scif_cleanup_zombie_epd () ; 
 int /*<<< orphan*/  scif_rma_destroy_tcw_invalid () ; 
 int /*<<< orphan*/  scif_rma_destroy_windows () ; 
 int /*<<< orphan*/  scif_rma_handle_remote_fences () ; 

void scif_misc_handler(struct work_struct *work)
{
	scif_rma_handle_remote_fences();
	scif_rma_destroy_windows();
	scif_rma_destroy_tcw_invalid();
	scif_cleanup_zombie_epd();
}