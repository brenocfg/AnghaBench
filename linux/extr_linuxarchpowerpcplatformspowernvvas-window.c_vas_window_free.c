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
struct vas_window {int winid; struct vas_instance* vinst; } ;
struct vas_instance {int /*<<< orphan*/  ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vas_window*) ; 
 int /*<<< orphan*/  unmap_winctx_mmio_bars (struct vas_window*) ; 
 int /*<<< orphan*/  vas_release_window_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vas_window_free_dbgdir (struct vas_window*) ; 

__attribute__((used)) static void vas_window_free(struct vas_window *window)
{
	int winid = window->winid;
	struct vas_instance *vinst = window->vinst;

	unmap_winctx_mmio_bars(window);

	vas_window_free_dbgdir(window);

	kfree(window);

	vas_release_window_id(&vinst->ida, winid);
}