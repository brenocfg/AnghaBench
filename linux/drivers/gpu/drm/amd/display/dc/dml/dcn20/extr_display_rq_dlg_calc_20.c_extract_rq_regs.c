#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int det_buffer_size_kbytes; } ;
struct display_mode_lib {TYPE_1__ ip; } ;
struct TYPE_16__ {void* swath_height; void* pte_row_height_linear; } ;
struct TYPE_26__ {int drq_expansion_mode; int prq_expansion_mode; int mrq_expansion_mode; int crq_expansion_mode; unsigned int plane1_base_address; TYPE_11__ rq_regs_c; TYPE_11__ rq_regs_l; } ;
typedef  TYPE_9__ display_rq_regs_st ;
struct TYPE_24__ {scalar_t__ stored_swath_bytes; } ;
struct TYPE_23__ {scalar_t__ stored_swath_bytes; } ;
struct TYPE_25__ {TYPE_7__ rq_c; TYPE_6__ rq_l; } ;
struct TYPE_17__ {int chunk_bytes; } ;
struct TYPE_22__ {TYPE_12__ rq_l; TYPE_12__ rq_c; } ;
struct TYPE_20__ {int /*<<< orphan*/  swath_height; int /*<<< orphan*/  dpte_row_height; } ;
struct TYPE_19__ {int /*<<< orphan*/  swath_height; int /*<<< orphan*/  dpte_row_height; } ;
struct TYPE_21__ {TYPE_3__ rq_c; TYPE_2__ rq_l; } ;
struct TYPE_15__ {TYPE_8__ misc; scalar_t__ yuv420; TYPE_5__ sizing; TYPE_4__ dlg; } ;
typedef  TYPE_10__ display_rq_params_st ;

/* Variables and functions */
 void* dml_floor (void*,int) ; 
 void* dml_log2 (int /*<<< orphan*/ ) ; 
 double dml_round_to_multiple (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_rq_sizing_regs (struct display_mode_lib*,TYPE_11__*,TYPE_12__) ; 

__attribute__((used)) static void extract_rq_regs(struct display_mode_lib *mode_lib,
		display_rq_regs_st *rq_regs,
		const display_rq_params_st rq_param)
{
	unsigned int detile_buf_size_in_bytes = mode_lib->ip.det_buffer_size_kbytes * 1024;
	unsigned int detile_buf_plane1_addr = 0;

	extract_rq_sizing_regs(mode_lib, &(rq_regs->rq_regs_l), rq_param.sizing.rq_l);

	rq_regs->rq_regs_l.pte_row_height_linear = dml_floor(dml_log2(rq_param.dlg.rq_l.dpte_row_height),
			1) - 3;

	if (rq_param.yuv420) {
		extract_rq_sizing_regs(mode_lib, &(rq_regs->rq_regs_c), rq_param.sizing.rq_c);
		rq_regs->rq_regs_c.pte_row_height_linear = dml_floor(dml_log2(rq_param.dlg.rq_c.dpte_row_height),
				1) - 3;
	}

	rq_regs->rq_regs_l.swath_height = dml_log2(rq_param.dlg.rq_l.swath_height);
	rq_regs->rq_regs_c.swath_height = dml_log2(rq_param.dlg.rq_c.swath_height);

	// FIXME: take the max between luma, chroma chunk size?
	// okay for now, as we are setting chunk_bytes to 8kb anyways
	if (rq_param.sizing.rq_l.chunk_bytes >= 32 * 1024) { //32kb
		rq_regs->drq_expansion_mode = 0;
	} else {
		rq_regs->drq_expansion_mode = 2;
	}
	rq_regs->prq_expansion_mode = 1;
	rq_regs->mrq_expansion_mode = 1;
	rq_regs->crq_expansion_mode = 1;

	if (rq_param.yuv420) {
		if ((double) rq_param.misc.rq_l.stored_swath_bytes
				/ (double) rq_param.misc.rq_c.stored_swath_bytes <= 1.5) {
			detile_buf_plane1_addr = (detile_buf_size_in_bytes / 2.0 / 64.0); // half to chroma
		} else {
			detile_buf_plane1_addr = dml_round_to_multiple((unsigned int) ((2.0 * detile_buf_size_in_bytes) / 3.0),
					256,
					0) / 64.0; // 2/3 to chroma
		}
	}
	rq_regs->plane1_base_address = detile_buf_plane1_addr;
}