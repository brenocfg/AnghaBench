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
typedef  int /*<<< orphan*/  u64 ;
struct vas_window {void* uwc_map; void* hvwc_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_hvwc_mmio_bar (struct vas_window*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_uwc_mmio_bar (struct vas_window*,int /*<<< orphan*/ *,int*) ; 
 void* map_mmio_region (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unmap_winctx_mmio_bars (struct vas_window*) ; 

int map_winctx_mmio_bars(struct vas_window *window)
{
	int len;
	u64 start;

	get_hvwc_mmio_bar(window, &start, &len);
	window->hvwc_map = map_mmio_region("HVWCM_Window", start, len);

	get_uwc_mmio_bar(window, &start, &len);
	window->uwc_map = map_mmio_region("UWCM_Window", start, len);

	if (!window->hvwc_map || !window->uwc_map) {
		unmap_winctx_mmio_bars(window);
		return -1;
	}

	return 0;
}