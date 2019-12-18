#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct parser_exec_state {scalar_t__ ring_id; TYPE_1__* vgpu; } ;
struct intel_gvt {int /*<<< orphan*/  dev_priv; } ;
struct TYPE_2__ {struct intel_gvt* gvt; } ;

/* Variables and functions */
 scalar_t__ BCS0 ; 
 int CMD_LEN (int) ; 
 int /*<<< orphan*/  DERRMR ; 
 int EBADRQC ; 
 int EFAULT ; 
 scalar_t__ IS_BROADWELL (int /*<<< orphan*/ ) ; 
 int MAX_VALID_LEN ; 
 scalar_t__ RCS0 ; 
 int cmd_length (struct parser_exec_state*) ; 
 scalar_t__ cmd_reg (struct parser_exec_state*,int) ; 
 int cmd_reg_handler (struct parser_exec_state*,scalar_t__,int,char*) ; 
 scalar_t__ cmd_reg_inhibit (struct parser_exec_state*,int) ; 
 int /*<<< orphan*/  gvt_err (char*,int,int) ; 
 scalar_t__ i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_handler_lri(struct parser_exec_state *s)
{
	int i, ret = 0;
	int cmd_len = cmd_length(s);
	struct intel_gvt *gvt = s->vgpu->gvt;
	u32 valid_len = CMD_LEN(1);

	/*
	 * Official intel docs are somewhat sloppy , check the definition of
	 * MI_LOAD_REGISTER_IMM.
	 */
	#define MAX_VALID_LEN 127
	if ((cmd_len < valid_len) || (cmd_len > MAX_VALID_LEN)) {
		gvt_err("len is not valid:  len=%u  valid_len=%u\n",
			cmd_len, valid_len);
		return -EFAULT;
	}

	for (i = 1; i < cmd_len; i += 2) {
		if (IS_BROADWELL(gvt->dev_priv) && s->ring_id != RCS0) {
			if (s->ring_id == BCS0 &&
			    cmd_reg(s, i) == i915_mmio_reg_offset(DERRMR))
				ret |= 0;
			else
				ret |= cmd_reg_inhibit(s, i) ? -EBADRQC : 0;
		}
		if (ret)
			break;
		ret |= cmd_reg_handler(s, cmd_reg(s, i), i, "lri");
		if (ret)
			break;
	}
	return ret;
}