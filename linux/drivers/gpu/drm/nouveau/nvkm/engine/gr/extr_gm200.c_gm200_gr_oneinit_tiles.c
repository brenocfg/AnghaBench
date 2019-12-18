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
struct gf100_gr {int gpc_nr; int tpc_total; int screen_tile_row_offset; int /*<<< orphan*/  tile; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_gr_oneinit_tiles (struct gf100_gr*) ; 
 int /*<<< orphan*/  gm200_gr_tile_map_2_8 ; 
 int /*<<< orphan*/  gm200_gr_tile_map_4_16 ; 
 int /*<<< orphan*/  gm200_gr_tile_map_6_24 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
gm200_gr_oneinit_tiles(struct gf100_gr *gr)
{
	/*XXX: Not sure what this is about.  The algorithm from NVGPU
	 *     seems to work for all boards I tried from earlier (and
	 *     later) GPUs except in these specific configurations.
	 *
	 *     Let's just hardcode them for now.
	 */
	if (gr->gpc_nr == 2 && gr->tpc_total == 8) {
		memcpy(gr->tile, gm200_gr_tile_map_2_8, gr->tpc_total);
		gr->screen_tile_row_offset = 1;
	} else
	if (gr->gpc_nr == 4 && gr->tpc_total == 16) {
		memcpy(gr->tile, gm200_gr_tile_map_4_16, gr->tpc_total);
		gr->screen_tile_row_offset = 4;
	} else
	if (gr->gpc_nr == 6 && gr->tpc_total == 24) {
		memcpy(gr->tile, gm200_gr_tile_map_6_24, gr->tpc_total);
		gr->screen_tile_row_offset = 5;
	} else {
		gf100_gr_oneinit_tiles(gr);
	}
}