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
struct TYPE_7__ {int /*<<< orphan*/  ptr_lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  function; } ;
struct TYPE_8__ {void* enable_metric_set; int /*<<< orphan*/  disable_metric_set; int /*<<< orphan*/ * is_valid_flex_reg; int /*<<< orphan*/  is_valid_mux_reg; void* is_valid_b_counter_reg; int /*<<< orphan*/  oa_hw_tail_read; int /*<<< orphan*/  read; int /*<<< orphan*/  oa_disable; int /*<<< orphan*/  oa_enable; int /*<<< orphan*/  init_oa_buffer; } ;
struct TYPE_10__ {int ctx_oactxctrl_offset; int ctx_flexeu0_offset; int gen8_valid_ctx_bit; TYPE_1__ oa_buffer; int /*<<< orphan*/  poll_wq; TYPE_5__ poll_check_timer; TYPE_2__ ops; int /*<<< orphan*/  oa_formats; } ;
struct TYPE_9__ {int initialized; int /*<<< orphan*/  metrics_idr; int /*<<< orphan*/  metrics_lock; int /*<<< orphan*/  sysctl_header; TYPE_4__ oa; int /*<<< orphan*/  lock; int /*<<< orphan*/  streams; } ;
struct drm_i915_private {TYPE_3__ perf; } ;
struct TYPE_12__ {int cs_timestamp_frequency_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ HAS_LOGICAL_RING_CONTEXTS (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_6__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_GEN8 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  chv_is_valid_mux_addr ; 
 int /*<<< orphan*/  dev_root ; 
 int /*<<< orphan*/  gen10_disable_metric_set ; 
 int /*<<< orphan*/  gen10_is_valid_mux_addr ; 
 int /*<<< orphan*/  gen7_init_oa_buffer ; 
 void* gen7_is_valid_b_counter_addr ; 
 int /*<<< orphan*/  gen7_oa_disable ; 
 int /*<<< orphan*/  gen7_oa_enable ; 
 int /*<<< orphan*/  gen7_oa_hw_tail_read ; 
 int /*<<< orphan*/  gen7_oa_read ; 
 int /*<<< orphan*/  gen8_disable_metric_set ; 
 void* gen8_enable_metric_set ; 
 int /*<<< orphan*/  gen8_init_oa_buffer ; 
 void* gen8_is_valid_flex_addr ; 
 int /*<<< orphan*/  gen8_is_valid_mux_addr ; 
 int /*<<< orphan*/  gen8_oa_disable ; 
 int /*<<< orphan*/  gen8_oa_enable ; 
 int /*<<< orphan*/  gen8_oa_hw_tail_read ; 
 int /*<<< orphan*/  gen8_oa_read ; 
 int /*<<< orphan*/  gen8_plus_oa_formats ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsw_disable_metric_set ; 
 void* hsw_enable_metric_set ; 
 int /*<<< orphan*/  hsw_is_valid_mux_addr ; 
 int /*<<< orphan*/  hsw_oa_formats ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oa_poll_check_timer_cb ; 
 int oa_sample_rate_hard_limit ; 
 int /*<<< orphan*/  register_sysctl_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void i915_perf_init(struct drm_i915_private *dev_priv)
{
	if (IS_HASWELL(dev_priv)) {
		dev_priv->perf.oa.ops.is_valid_b_counter_reg =
			gen7_is_valid_b_counter_addr;
		dev_priv->perf.oa.ops.is_valid_mux_reg =
			hsw_is_valid_mux_addr;
		dev_priv->perf.oa.ops.is_valid_flex_reg = NULL;
		dev_priv->perf.oa.ops.init_oa_buffer = gen7_init_oa_buffer;
		dev_priv->perf.oa.ops.enable_metric_set = hsw_enable_metric_set;
		dev_priv->perf.oa.ops.disable_metric_set = hsw_disable_metric_set;
		dev_priv->perf.oa.ops.oa_enable = gen7_oa_enable;
		dev_priv->perf.oa.ops.oa_disable = gen7_oa_disable;
		dev_priv->perf.oa.ops.read = gen7_oa_read;
		dev_priv->perf.oa.ops.oa_hw_tail_read =
			gen7_oa_hw_tail_read;

		dev_priv->perf.oa.oa_formats = hsw_oa_formats;
	} else if (HAS_LOGICAL_RING_CONTEXTS(dev_priv)) {
		/* Note: that although we could theoretically also support the
		 * legacy ringbuffer mode on BDW (and earlier iterations of
		 * this driver, before upstreaming did this) it didn't seem
		 * worth the complexity to maintain now that BDW+ enable
		 * execlist mode by default.
		 */
		dev_priv->perf.oa.oa_formats = gen8_plus_oa_formats;

		dev_priv->perf.oa.ops.init_oa_buffer = gen8_init_oa_buffer;
		dev_priv->perf.oa.ops.oa_enable = gen8_oa_enable;
		dev_priv->perf.oa.ops.oa_disable = gen8_oa_disable;
		dev_priv->perf.oa.ops.read = gen8_oa_read;
		dev_priv->perf.oa.ops.oa_hw_tail_read = gen8_oa_hw_tail_read;

		if (IS_GEN8(dev_priv) || IS_GEN9(dev_priv)) {
			dev_priv->perf.oa.ops.is_valid_b_counter_reg =
				gen7_is_valid_b_counter_addr;
			dev_priv->perf.oa.ops.is_valid_mux_reg =
				gen8_is_valid_mux_addr;
			dev_priv->perf.oa.ops.is_valid_flex_reg =
				gen8_is_valid_flex_addr;

			if (IS_CHERRYVIEW(dev_priv)) {
				dev_priv->perf.oa.ops.is_valid_mux_reg =
					chv_is_valid_mux_addr;
			}

			dev_priv->perf.oa.ops.enable_metric_set = gen8_enable_metric_set;
			dev_priv->perf.oa.ops.disable_metric_set = gen8_disable_metric_set;

			if (IS_GEN8(dev_priv)) {
				dev_priv->perf.oa.ctx_oactxctrl_offset = 0x120;
				dev_priv->perf.oa.ctx_flexeu0_offset = 0x2ce;

				dev_priv->perf.oa.gen8_valid_ctx_bit = (1<<25);
			} else {
				dev_priv->perf.oa.ctx_oactxctrl_offset = 0x128;
				dev_priv->perf.oa.ctx_flexeu0_offset = 0x3de;

				dev_priv->perf.oa.gen8_valid_ctx_bit = (1<<16);
			}
		} else if (IS_GEN(dev_priv, 10, 11)) {
			dev_priv->perf.oa.ops.is_valid_b_counter_reg =
				gen7_is_valid_b_counter_addr;
			dev_priv->perf.oa.ops.is_valid_mux_reg =
				gen10_is_valid_mux_addr;
			dev_priv->perf.oa.ops.is_valid_flex_reg =
				gen8_is_valid_flex_addr;

			dev_priv->perf.oa.ops.enable_metric_set = gen8_enable_metric_set;
			dev_priv->perf.oa.ops.disable_metric_set = gen10_disable_metric_set;

			dev_priv->perf.oa.ctx_oactxctrl_offset = 0x128;
			dev_priv->perf.oa.ctx_flexeu0_offset = 0x3de;

			dev_priv->perf.oa.gen8_valid_ctx_bit = (1<<16);
		}
	}

	if (dev_priv->perf.oa.ops.enable_metric_set) {
		hrtimer_init(&dev_priv->perf.oa.poll_check_timer,
				CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		dev_priv->perf.oa.poll_check_timer.function = oa_poll_check_timer_cb;
		init_waitqueue_head(&dev_priv->perf.oa.poll_wq);

		INIT_LIST_HEAD(&dev_priv->perf.streams);
		mutex_init(&dev_priv->perf.lock);
		spin_lock_init(&dev_priv->perf.oa.oa_buffer.ptr_lock);

		oa_sample_rate_hard_limit = 1000 *
			(INTEL_INFO(dev_priv)->cs_timestamp_frequency_khz / 2);
		dev_priv->perf.sysctl_header = register_sysctl_table(dev_root);

		mutex_init(&dev_priv->perf.metrics_lock);
		idr_init(&dev_priv->perf.metrics_idr);

		dev_priv->perf.initialized = true;
	}
}