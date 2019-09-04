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
struct vmw_ctx_binding_state {int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned long VMW_BINDING_NUM_BITS ; 
#define  VMW_BINDING_PS_BIT 131 
#define  VMW_BINDING_RT_BIT 130 
#define  VMW_BINDING_SO_BIT 129 
#define  VMW_BINDING_VB_BIT 128 
 int /*<<< orphan*/  __clear_bit (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long find_next_bit (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int vmw_binding_emit_dirty_ps (struct vmw_ctx_binding_state*) ; 
 int vmw_emit_set_rt (struct vmw_ctx_binding_state*) ; 
 int vmw_emit_set_so (struct vmw_ctx_binding_state*) ; 
 int vmw_emit_set_vb (struct vmw_ctx_binding_state*) ; 

__attribute__((used)) static int vmw_binding_emit_dirty(struct vmw_ctx_binding_state *cbs)
{
	int ret = 0;
	unsigned long hit = 0;

	while ((hit = find_next_bit(&cbs->dirty, VMW_BINDING_NUM_BITS, hit))
	      < VMW_BINDING_NUM_BITS) {

		switch (hit) {
		case VMW_BINDING_RT_BIT:
			ret = vmw_emit_set_rt(cbs);
			break;
		case VMW_BINDING_PS_BIT:
			ret = vmw_binding_emit_dirty_ps(cbs);
			break;
		case VMW_BINDING_SO_BIT:
			ret = vmw_emit_set_so(cbs);
			break;
		case VMW_BINDING_VB_BIT:
			ret = vmw_emit_set_vb(cbs);
			break;
		default:
			BUG();
		}
		if (ret)
			return ret;

		__clear_bit(hit, &cbs->dirty);
		hit++;
	}

	return 0;
}