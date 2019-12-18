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
struct venus_inst {struct venus_core* core; } ;
struct venus_core {int dummy; } ;

/* Variables and functions */
 int hfi_session_load_res (struct venus_inst*) ; 
 int hfi_session_start (struct venus_inst*) ; 
 int /*<<< orphan*/  hfi_session_unload_res (struct venus_inst*) ; 
 int session_register_bufs (struct venus_inst*) ; 
 int venus_helper_intbufs_alloc (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_intbufs_free (struct venus_inst*) ; 
 int /*<<< orphan*/  venus_helper_load_scale_clocks (struct venus_core*) ; 
 int /*<<< orphan*/  venus_helper_unregister_bufs (struct venus_inst*) ; 

int venus_helper_vb2_start_streaming(struct venus_inst *inst)
{
	struct venus_core *core = inst->core;
	int ret;

	ret = venus_helper_intbufs_alloc(inst);
	if (ret)
		return ret;

	ret = session_register_bufs(inst);
	if (ret)
		goto err_bufs_free;

	venus_helper_load_scale_clocks(core);

	ret = hfi_session_load_res(inst);
	if (ret)
		goto err_unreg_bufs;

	ret = hfi_session_start(inst);
	if (ret)
		goto err_unload_res;

	return 0;

err_unload_res:
	hfi_session_unload_res(inst);
err_unreg_bufs:
	venus_helper_unregister_bufs(inst);
err_bufs_free:
	venus_helper_intbufs_free(inst);
	return ret;
}