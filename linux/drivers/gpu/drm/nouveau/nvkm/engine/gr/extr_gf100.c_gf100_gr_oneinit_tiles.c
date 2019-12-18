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
typedef  int u8 ;
typedef  int u32 ;
struct gf100_gr {int tpc_total; int screen_tile_row_offset; int gpc_nr; int* tpc_nr; int tpc_max; int* tile; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int GPC_MAX ; 

void
gf100_gr_oneinit_tiles(struct gf100_gr *gr)
{
	static const u8 primes[] = {
		3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61
	};
	int init_frac[GPC_MAX], init_err[GPC_MAX], run_err[GPC_MAX], i, j;
	u32 mul_factor, comm_denom;
	u8  gpc_map[GPC_MAX];
	bool sorted;

	switch (gr->tpc_total) {
	case 15: gr->screen_tile_row_offset = 0x06; break;
	case 14: gr->screen_tile_row_offset = 0x05; break;
	case 13: gr->screen_tile_row_offset = 0x02; break;
	case 11: gr->screen_tile_row_offset = 0x07; break;
	case 10: gr->screen_tile_row_offset = 0x06; break;
	case  7:
	case  5: gr->screen_tile_row_offset = 0x01; break;
	case  3: gr->screen_tile_row_offset = 0x02; break;
	case  2:
	case  1: gr->screen_tile_row_offset = 0x01; break;
	default: gr->screen_tile_row_offset = 0x03;
		for (i = 0; i < ARRAY_SIZE(primes); i++) {
			if (gr->tpc_total % primes[i]) {
				gr->screen_tile_row_offset = primes[i];
				break;
			}
		}
		break;
	}

	/* Sort GPCs by TPC count, highest-to-lowest. */
	for (i = 0; i < gr->gpc_nr; i++)
		gpc_map[i] = i;
	sorted = false;

	while (!sorted) {
		for (sorted = true, i = 0; i < gr->gpc_nr - 1; i++) {
			if (gr->tpc_nr[gpc_map[i + 1]] >
			    gr->tpc_nr[gpc_map[i + 0]]) {
				u8 swap = gpc_map[i];
				gpc_map[i + 0] = gpc_map[i + 1];
				gpc_map[i + 1] = swap;
				sorted = false;
			}
		}
	}

	/* Determine tile->GPC mapping */
	mul_factor = gr->gpc_nr * gr->tpc_max;
	if (mul_factor & 1)
		mul_factor = 2;
	else
		mul_factor = 1;

	comm_denom = gr->gpc_nr * gr->tpc_max * mul_factor;

	for (i = 0; i < gr->gpc_nr; i++) {
		init_frac[i] = gr->tpc_nr[gpc_map[i]] * gr->gpc_nr * mul_factor;
		 init_err[i] = i * gr->tpc_max * mul_factor - comm_denom/2;
		  run_err[i] = init_frac[i] + init_err[i];
	}

	for (i = 0; i < gr->tpc_total;) {
		for (j = 0; j < gr->gpc_nr; j++) {
			if ((run_err[j] * 2) >= comm_denom) {
				gr->tile[i++] = gpc_map[j];
				run_err[j] += init_frac[j] - comm_denom;
			} else {
				run_err[j] += init_frac[j];
			}
		}
	}
}