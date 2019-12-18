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
struct TYPE_4__ {int /*<<< orphan*/  setup_cdp; int /*<<< orphan*/  get_scaler_ver; int /*<<< orphan*/  setup_scaler; int /*<<< orphan*/  setup_multirect; int /*<<< orphan*/  setup_csc; int /*<<< orphan*/  setup_qos_ctrl; int /*<<< orphan*/  setup_creq_lut; int /*<<< orphan*/  setup_danger_safe_lut; int /*<<< orphan*/  setup_pe; int /*<<< orphan*/  setup_solidfill; int /*<<< orphan*/  setup_sourceaddress; int /*<<< orphan*/  setup_rects; int /*<<< orphan*/  setup_format; } ;
struct dpu_hw_pipe {TYPE_2__ ops; TYPE_1__* cap; } ;
struct TYPE_3__ {unsigned long features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_SSPP_CDP ; 
 int /*<<< orphan*/  DPU_SSPP_CSC ; 
 int /*<<< orphan*/  DPU_SSPP_CSC_10BIT ; 
 int /*<<< orphan*/  DPU_SSPP_QOS ; 
 int /*<<< orphan*/  DPU_SSPP_SCALER_QSEED3 ; 
 int /*<<< orphan*/  DPU_SSPP_SMART_DMA_V1 ; 
 int /*<<< orphan*/  DPU_SSPP_SMART_DMA_V2 ; 
 int /*<<< orphan*/  DPU_SSPP_SRC ; 
 int /*<<< orphan*/  _dpu_hw_sspp_get_scaler3_ver ; 
 int /*<<< orphan*/  _dpu_hw_sspp_setup_scaler3 ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_cdp ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_creq_lut ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_csc ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_danger_safe_lut ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_format ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_multirect ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_pe_config ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_qos_ctrl ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_rects ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_solidfill ; 
 int /*<<< orphan*/  dpu_hw_sspp_setup_sourceaddress ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void _setup_layer_ops(struct dpu_hw_pipe *c,
		unsigned long features)
{
	if (test_bit(DPU_SSPP_SRC, &features)) {
		c->ops.setup_format = dpu_hw_sspp_setup_format;
		c->ops.setup_rects = dpu_hw_sspp_setup_rects;
		c->ops.setup_sourceaddress = dpu_hw_sspp_setup_sourceaddress;
		c->ops.setup_solidfill = dpu_hw_sspp_setup_solidfill;
		c->ops.setup_pe = dpu_hw_sspp_setup_pe_config;
	}

	if (test_bit(DPU_SSPP_QOS, &features)) {
		c->ops.setup_danger_safe_lut =
			dpu_hw_sspp_setup_danger_safe_lut;
		c->ops.setup_creq_lut = dpu_hw_sspp_setup_creq_lut;
		c->ops.setup_qos_ctrl = dpu_hw_sspp_setup_qos_ctrl;
	}

	if (test_bit(DPU_SSPP_CSC, &features) ||
		test_bit(DPU_SSPP_CSC_10BIT, &features))
		c->ops.setup_csc = dpu_hw_sspp_setup_csc;

	if (test_bit(DPU_SSPP_SMART_DMA_V1, &c->cap->features) ||
		test_bit(DPU_SSPP_SMART_DMA_V2, &c->cap->features))
		c->ops.setup_multirect = dpu_hw_sspp_setup_multirect;

	if (test_bit(DPU_SSPP_SCALER_QSEED3, &features)) {
		c->ops.setup_scaler = _dpu_hw_sspp_setup_scaler3;
		c->ops.get_scaler_ver = _dpu_hw_sspp_get_scaler3_ver;
	}

	if (test_bit(DPU_SSPP_CDP, &features))
		c->ops.setup_cdp = dpu_hw_sspp_setup_cdp;
}