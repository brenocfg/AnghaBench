#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int stream_enc_count; unsigned int pipe_count; unsigned int audio_count; unsigned int clk_src_count; int /*<<< orphan*/ * pp_smu; int /*<<< orphan*/ * dmcu; int /*<<< orphan*/ * abm; int /*<<< orphan*/ * dp_clock_source; int /*<<< orphan*/ ** clock_sources; scalar_t__* audios; int /*<<< orphan*/ ** sw_i2cs; int /*<<< orphan*/ ** hw_i2cs; int /*<<< orphan*/ ** engines; TYPE_3__* res_cap; int /*<<< orphan*/ ** timing_generators; int /*<<< orphan*/ * irqs; int /*<<< orphan*/ ** hubps; TYPE_5__** ipps; int /*<<< orphan*/ ** dpps; TYPE_6__** opps; int /*<<< orphan*/ * hubbub; int /*<<< orphan*/ * mpc; int /*<<< orphan*/ ** stream_enc; } ;
struct dcn10_resource_pool {TYPE_4__ base; } ;
struct TYPE_12__ {TYPE_1__* funcs; } ;
struct TYPE_11__ {TYPE_2__* funcs; } ;
struct TYPE_9__ {unsigned int num_ddc; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* ipp_destroy ) (TYPE_5__**) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* opp_destroy ) (TYPE_6__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * DCN10STRENC_FROM_STRENC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DCN10TG_FROM_TG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TO_DCN10_HUBP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TO_DCN10_MPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dal_irq_service_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce110_engine_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_abm_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_aud_destroy (scalar_t__*) ; 
 int /*<<< orphan*/  dce_dmcu_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dcn10_clock_source_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dcn10_dpp_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__**) ; 

__attribute__((used)) static void destruct(struct dcn10_resource_pool *pool)
{
	unsigned int i;

	for (i = 0; i < pool->base.stream_enc_count; i++) {
		if (pool->base.stream_enc[i] != NULL) {
			kfree(DCN10STRENC_FROM_STRENC(pool->base.stream_enc[i]));
			pool->base.stream_enc[i] = NULL;
		}
	}

	if (pool->base.mpc != NULL) {
		kfree(TO_DCN10_MPC(pool->base.mpc));
		pool->base.mpc = NULL;
	}

	if (pool->base.hubbub != NULL) {
		kfree(pool->base.hubbub);
		pool->base.hubbub = NULL;
	}

	for (i = 0; i < pool->base.pipe_count; i++) {
		if (pool->base.opps[i] != NULL)
			pool->base.opps[i]->funcs->opp_destroy(&pool->base.opps[i]);

		if (pool->base.dpps[i] != NULL)
			dcn10_dpp_destroy(&pool->base.dpps[i]);

		if (pool->base.ipps[i] != NULL)
			pool->base.ipps[i]->funcs->ipp_destroy(&pool->base.ipps[i]);

		if (pool->base.hubps[i] != NULL) {
			kfree(TO_DCN10_HUBP(pool->base.hubps[i]));
			pool->base.hubps[i] = NULL;
		}

		if (pool->base.irqs != NULL) {
			dal_irq_service_destroy(&pool->base.irqs);
		}

		if (pool->base.timing_generators[i] != NULL)	{
			kfree(DCN10TG_FROM_TG(pool->base.timing_generators[i]));
			pool->base.timing_generators[i] = NULL;
		}
	}

	for (i = 0; i < pool->base.res_cap->num_ddc; i++) {
		if (pool->base.engines[i] != NULL)
			dce110_engine_destroy(&pool->base.engines[i]);
		if (pool->base.hw_i2cs[i] != NULL) {
			kfree(pool->base.hw_i2cs[i]);
			pool->base.hw_i2cs[i] = NULL;
		}
		if (pool->base.sw_i2cs[i] != NULL) {
			kfree(pool->base.sw_i2cs[i]);
			pool->base.sw_i2cs[i] = NULL;
		}
	}

	for (i = 0; i < pool->base.audio_count; i++) {
		if (pool->base.audios[i])
			dce_aud_destroy(&pool->base.audios[i]);
	}

	for (i = 0; i < pool->base.clk_src_count; i++) {
		if (pool->base.clock_sources[i] != NULL) {
			dcn10_clock_source_destroy(&pool->base.clock_sources[i]);
			pool->base.clock_sources[i] = NULL;
		}
	}

	if (pool->base.dp_clock_source != NULL) {
		dcn10_clock_source_destroy(&pool->base.dp_clock_source);
		pool->base.dp_clock_source = NULL;
	}

	if (pool->base.abm != NULL)
		dce_abm_destroy(&pool->base.abm);

	if (pool->base.dmcu != NULL)
		dce_dmcu_destroy(&pool->base.dmcu);

	kfree(pool->base.pp_smu);
}