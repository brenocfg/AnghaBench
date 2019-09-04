#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int stream_enc_count; unsigned int pipe_count; unsigned int audio_count; unsigned int clk_src_count; int /*<<< orphan*/ * pp_smu; int /*<<< orphan*/ * dccg; int /*<<< orphan*/ * dmcu; int /*<<< orphan*/ * abm; int /*<<< orphan*/ * dp_clock_source; int /*<<< orphan*/ ** clock_sources; scalar_t__* audios; int /*<<< orphan*/ ** stream_enc; TYPE_5__** engines; int /*<<< orphan*/ ** timing_generators; int /*<<< orphan*/ * irqs; int /*<<< orphan*/ ** hubps; TYPE_6__** ipps; int /*<<< orphan*/ ** dpps; TYPE_7__** opps; int /*<<< orphan*/ * hubbub; int /*<<< orphan*/ * mpc; } ;
struct dcn10_resource_pool {TYPE_4__ base; } ;
struct TYPE_14__ {TYPE_1__* funcs; } ;
struct TYPE_13__ {TYPE_2__* funcs; } ;
struct TYPE_12__ {TYPE_3__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* destroy_engine ) (TYPE_5__**) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* ipp_destroy ) (TYPE_6__**) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* opp_destroy ) (TYPE_7__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * DCN10TG_FROM_TG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TO_DCN10_HUBP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TO_DCN10_MPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dal_irq_service_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_abm_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_aud_destroy (scalar_t__*) ; 
 int /*<<< orphan*/  dce_dccg_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_dmcu_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dcn10_clock_source_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dcn10_dpp_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__**) ; 

__attribute__((used)) static void destruct(struct dcn10_resource_pool *pool)
{
	unsigned int i;

	for (i = 0; i < pool->base.stream_enc_count; i++) {
		if (pool->base.stream_enc[i] != NULL) {
			/* TODO: free dcn version of stream encoder once implemented
			 * rather than using virtual stream encoder
			 */
			kfree(pool->base.stream_enc[i]);
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

		if (pool->base.engines[i] != NULL)
			pool->base.engines[i]->funcs->destroy_engine(&pool->base.engines[i]);
	}

	for (i = 0; i < pool->base.stream_enc_count; i++)
		kfree(pool->base.stream_enc[i]);

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

	if (pool->base.dccg != NULL)
		dce_dccg_destroy(&pool->base.dccg);

	kfree(pool->base.pp_smu);
}