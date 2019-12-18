#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int pipe_count; unsigned int audio_count; unsigned int stream_enc_count; unsigned int clk_src_count; int /*<<< orphan*/ * dmcu; int /*<<< orphan*/ * abm; int /*<<< orphan*/ * dp_clock_source; int /*<<< orphan*/ ** clock_sources; int /*<<< orphan*/ ** stream_enc; scalar_t__* audios; int /*<<< orphan*/ ** sw_i2cs; int /*<<< orphan*/ ** hw_i2cs; int /*<<< orphan*/ ** engines; TYPE_1__* res_cap; int /*<<< orphan*/ ** timing_generators; int /*<<< orphan*/ * irqs; int /*<<< orphan*/ ** mis; int /*<<< orphan*/ ** ipps; int /*<<< orphan*/ ** transforms; int /*<<< orphan*/ ** opps; } ;
struct dce110_resource_pool {TYPE_2__ base; } ;
struct TYPE_3__ {unsigned int num_ddc; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DCE110STRENC_FROM_STRENC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DCE110TG_FROM_TG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TO_DCE_MEM_INPUT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dal_irq_service_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce110_engine_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce110_opp_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce120_clock_source_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce120_transform_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_abm_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_aud_destroy (scalar_t__*) ; 
 int /*<<< orphan*/  dce_dmcu_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dce_ipp_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destruct(struct dce110_resource_pool *pool)
{
	unsigned int i;

	for (i = 0; i < pool->base.pipe_count; i++) {
		if (pool->base.opps[i] != NULL)
			dce110_opp_destroy(&pool->base.opps[i]);

		if (pool->base.transforms[i] != NULL)
			dce120_transform_destroy(&pool->base.transforms[i]);

		if (pool->base.ipps[i] != NULL)
			dce_ipp_destroy(&pool->base.ipps[i]);

		if (pool->base.mis[i] != NULL) {
			kfree(TO_DCE_MEM_INPUT(pool->base.mis[i]));
			pool->base.mis[i] = NULL;
		}

		if (pool->base.irqs != NULL) {
			dal_irq_service_destroy(&pool->base.irqs);
		}

		if (pool->base.timing_generators[i] != NULL) {
			kfree(DCE110TG_FROM_TG(pool->base.timing_generators[i]));
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

	for (i = 0; i < pool->base.stream_enc_count; i++) {
		if (pool->base.stream_enc[i] != NULL)
			kfree(DCE110STRENC_FROM_STRENC(pool->base.stream_enc[i]));
	}

	for (i = 0; i < pool->base.clk_src_count; i++) {
		if (pool->base.clock_sources[i] != NULL)
			dce120_clock_source_destroy(
				&pool->base.clock_sources[i]);
	}

	if (pool->base.dp_clock_source != NULL)
		dce120_clock_source_destroy(&pool->base.dp_clock_source);

	if (pool->base.abm != NULL)
		dce_abm_destroy(&pool->base.abm);

	if (pool->base.dmcu != NULL)
		dce_dmcu_destroy(&pool->base.dmcu);
}