#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {int tv_nsec; scalar_t__ tv_sec; } ;
struct intel_csr {int /*<<< orphan*/  version; int /*<<< orphan*/ * dmc_payload; } ;
struct TYPE_14__ {int /*<<< orphan*/  platform; } ;
struct i915_gpu_state {int epoch; int ngtier; int* gtier; int nfence; int* fence; int fault_data1; int fault_data0; int /*<<< orphan*/  uc; int /*<<< orphan*/  params; int /*<<< orphan*/  driver_caps; int /*<<< orphan*/  runtime_info; TYPE_5__ device_info; scalar_t__ display; scalar_t__ overlay; struct drm_i915_error_engine* engine; int /*<<< orphan*/  err_int; int /*<<< orphan*/  done_reg; int /*<<< orphan*/  error; int /*<<< orphan*/  ccid; int /*<<< orphan*/  derrmr; int /*<<< orphan*/  forcewake; int /*<<< orphan*/  pgtbl_er; int /*<<< orphan*/  ier; int /*<<< orphan*/  eir; int /*<<< orphan*/  suspended; int /*<<< orphan*/  wakelock; int /*<<< orphan*/  awake; int /*<<< orphan*/  iommu; int /*<<< orphan*/  suspend_count; int /*<<< orphan*/  reset_count; int /*<<< orphan*/  capture; int /*<<< orphan*/  uptime; int /*<<< orphan*/  boottime; int /*<<< orphan*/  time; scalar_t__* error_msg; } ;
struct drm_i915_error_state_buf {TYPE_4__* i915; } ;
struct drm_i915_error_object {int /*<<< orphan*/  gtt_offset; } ;
struct TYPE_10__ {int comm; int pid; } ;
struct drm_i915_error_engine {int user_bo_count; int num_requests; struct drm_i915_error_object const* default_state; TYPE_2__* engine; struct drm_i915_error_object const* wa_batchbuffer; struct drm_i915_error_object const* wa_ctx; struct drm_i915_error_object const* ctx; struct drm_i915_error_object const* hws_page; struct drm_i915_error_object const* ringbuffer; int /*<<< orphan*/ * requests; struct drm_i915_error_object const** user_bo; TYPE_1__ context; struct drm_i915_error_object* batchbuffer; struct drm_i915_error_engine* next; } ;
typedef  int s64 ;
struct TYPE_13__ {struct intel_csr csr; } ;
struct TYPE_12__ {int release; int machine; } ;
struct TYPE_11__ {int name; } ;

/* Variables and functions */
 int CSR_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int CSR_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRIVER_DATE ; 
 scalar_t__ HAS_CSR (TYPE_4__*) ; 
 int HZ ; 
 int INTEL_GEN (TYPE_4__*) ; 
 scalar_t__ IS_GEN (TYPE_4__*,int) ; 
 scalar_t__ IS_GEN_RANGE (TYPE_4__*,int,int) ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  err_print_capabilities (struct drm_i915_error_state_buf*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err_print_params (struct drm_i915_error_state_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err_print_pciid (struct drm_i915_error_state_buf*,TYPE_4__*) ; 
 int /*<<< orphan*/  err_print_uc (struct drm_i915_error_state_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err_printf (struct drm_i915_error_state_buf*,char*,int,...) ; 
 int /*<<< orphan*/  err_puts (struct drm_i915_error_state_buf*,int) ; 
 int /*<<< orphan*/  error_print_engine (struct drm_i915_error_state_buf*,struct drm_i915_error_engine const*,int) ; 
 int /*<<< orphan*/  error_print_request (struct drm_i915_error_state_buf*,char*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* init_utsname () ; 
 int /*<<< orphan*/  intel_display_print_error_state (struct drm_i915_error_state_buf*,scalar_t__) ; 
 int /*<<< orphan*/  intel_overlay_print_error_state (struct drm_i915_error_state_buf*,scalar_t__) ; 
 int /*<<< orphan*/  intel_platform_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_subplatform (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_error_obj (struct drm_i915_error_state_buf*,TYPE_2__*,char*,struct drm_i915_error_object const*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __err_print_to_sgl(struct drm_i915_error_state_buf *m,
			       struct i915_gpu_state *error)
{
	const struct drm_i915_error_engine *ee;
	struct timespec64 ts;
	int i, j;

	if (*error->error_msg)
		err_printf(m, "%s\n", error->error_msg);
	err_printf(m, "Kernel: %s %s\n",
		   init_utsname()->release,
		   init_utsname()->machine);
	err_printf(m, "Driver: %s\n", DRIVER_DATE);
	ts = ktime_to_timespec64(error->time);
	err_printf(m, "Time: %lld s %ld us\n",
		   (s64)ts.tv_sec, ts.tv_nsec / NSEC_PER_USEC);
	ts = ktime_to_timespec64(error->boottime);
	err_printf(m, "Boottime: %lld s %ld us\n",
		   (s64)ts.tv_sec, ts.tv_nsec / NSEC_PER_USEC);
	ts = ktime_to_timespec64(error->uptime);
	err_printf(m, "Uptime: %lld s %ld us\n",
		   (s64)ts.tv_sec, ts.tv_nsec / NSEC_PER_USEC);
	err_printf(m, "Epoch: %lu jiffies (%u HZ)\n", error->epoch, HZ);
	err_printf(m, "Capture: %lu jiffies; %d ms ago, %d ms after epoch\n",
		   error->capture,
		   jiffies_to_msecs(jiffies - error->capture),
		   jiffies_to_msecs(error->capture - error->epoch));

	for (ee = error->engine; ee; ee = ee->next)
		err_printf(m, "Active process (on ring %s): %s [%d]\n",
			   ee->engine->name,
			   ee->context.comm,
			   ee->context.pid);

	err_printf(m, "Reset count: %u\n", error->reset_count);
	err_printf(m, "Suspend count: %u\n", error->suspend_count);
	err_printf(m, "Platform: %s\n", intel_platform_name(error->device_info.platform));
	err_printf(m, "Subplatform: 0x%x\n",
		   intel_subplatform(&error->runtime_info,
				     error->device_info.platform));
	err_print_pciid(m, m->i915);

	err_printf(m, "IOMMU enabled?: %d\n", error->iommu);

	if (HAS_CSR(m->i915)) {
		struct intel_csr *csr = &m->i915->csr;

		err_printf(m, "DMC loaded: %s\n",
			   yesno(csr->dmc_payload != NULL));
		err_printf(m, "DMC fw version: %d.%d\n",
			   CSR_VERSION_MAJOR(csr->version),
			   CSR_VERSION_MINOR(csr->version));
	}

	err_printf(m, "GT awake: %s\n", yesno(error->awake));
	err_printf(m, "RPM wakelock: %s\n", yesno(error->wakelock));
	err_printf(m, "PM suspended: %s\n", yesno(error->suspended));
	err_printf(m, "EIR: 0x%08x\n", error->eir);
	err_printf(m, "IER: 0x%08x\n", error->ier);
	for (i = 0; i < error->ngtier; i++)
		err_printf(m, "GTIER[%d]: 0x%08x\n", i, error->gtier[i]);
	err_printf(m, "PGTBL_ER: 0x%08x\n", error->pgtbl_er);
	err_printf(m, "FORCEWAKE: 0x%08x\n", error->forcewake);
	err_printf(m, "DERRMR: 0x%08x\n", error->derrmr);
	err_printf(m, "CCID: 0x%08x\n", error->ccid);

	for (i = 0; i < error->nfence; i++)
		err_printf(m, "  fence[%d] = %08llx\n", i, error->fence[i]);

	if (IS_GEN_RANGE(m->i915, 6, 11)) {
		err_printf(m, "ERROR: 0x%08x\n", error->error);
		err_printf(m, "DONE_REG: 0x%08x\n", error->done_reg);
	}

	if (INTEL_GEN(m->i915) >= 8)
		err_printf(m, "FAULT_TLB_DATA: 0x%08x 0x%08x\n",
			   error->fault_data1, error->fault_data0);

	if (IS_GEN(m->i915, 7))
		err_printf(m, "ERR_INT: 0x%08x\n", error->err_int);

	for (ee = error->engine; ee; ee = ee->next)
		error_print_engine(m, ee, error->epoch);

	for (ee = error->engine; ee; ee = ee->next) {
		const struct drm_i915_error_object *obj;

		obj = ee->batchbuffer;
		if (obj) {
			err_puts(m, ee->engine->name);
			if (ee->context.pid)
				err_printf(m, " (submitted by %s [%d])",
					   ee->context.comm,
					   ee->context.pid);
			err_printf(m, " --- gtt_offset = 0x%08x %08x\n",
				   upper_32_bits(obj->gtt_offset),
				   lower_32_bits(obj->gtt_offset));
			print_error_obj(m, ee->engine, NULL, obj);
		}

		for (j = 0; j < ee->user_bo_count; j++)
			print_error_obj(m, ee->engine, "user", ee->user_bo[j]);

		if (ee->num_requests) {
			err_printf(m, "%s --- %d requests\n",
				   ee->engine->name,
				   ee->num_requests);
			for (j = 0; j < ee->num_requests; j++)
				error_print_request(m, " ",
						    &ee->requests[j],
						    error->epoch);
		}

		print_error_obj(m, ee->engine, "ringbuffer", ee->ringbuffer);
		print_error_obj(m, ee->engine, "HW Status", ee->hws_page);
		print_error_obj(m, ee->engine, "HW context", ee->ctx);
		print_error_obj(m, ee->engine, "WA context", ee->wa_ctx);
		print_error_obj(m, ee->engine,
				"WA batchbuffer", ee->wa_batchbuffer);
		print_error_obj(m, ee->engine,
				"NULL context", ee->default_state);
	}

	if (error->overlay)
		intel_overlay_print_error_state(m, error->overlay);

	if (error->display)
		intel_display_print_error_state(m, error->display);

	err_print_capabilities(m, &error->device_info, &error->runtime_info,
			       &error->driver_caps);
	err_print_params(m, &error->params);
	err_print_uc(m, &error->uc);
}