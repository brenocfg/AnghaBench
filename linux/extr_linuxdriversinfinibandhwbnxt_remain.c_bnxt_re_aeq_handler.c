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
typedef  scalar_t__ u8 ;
struct creq_qp_event {int dummy; } ;
struct creq_func_event {int dummy; } ;
struct creq_base {scalar_t__ type; } ;
struct bnxt_qplib_rcfw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CREQ_BASE_TYPE_FUNC_EVENT ; 
 int bnxt_re_handle_affi_async_event (struct creq_qp_event*,void*) ; 
 int bnxt_re_handle_unaffi_async_event (struct creq_func_event*) ; 

__attribute__((used)) static int bnxt_re_aeq_handler(struct bnxt_qplib_rcfw *rcfw,
			       void *aeqe, void *obj)
{
	struct creq_qp_event *affi_async;
	struct creq_func_event *unaffi_async;
	u8 type;
	int rc;

	type = ((struct creq_base *)aeqe)->type;
	if (type == CREQ_BASE_TYPE_FUNC_EVENT) {
		unaffi_async = aeqe;
		rc = bnxt_re_handle_unaffi_async_event(unaffi_async);
	} else {
		affi_async = aeqe;
		rc = bnxt_re_handle_affi_async_event(affi_async, obj);
	}

	return rc;
}