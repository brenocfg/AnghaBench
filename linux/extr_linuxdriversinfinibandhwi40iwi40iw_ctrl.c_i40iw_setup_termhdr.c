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
typedef  void* u8 ;
struct i40iw_terminate_hdr {void* error_code; void* layer_etype; } ;
struct i40iw_sc_qp {int flush_code; } ;
typedef  enum i40iw_flush_opcode { ____Placeholder_i40iw_flush_opcode } i40iw_flush_opcode ;

/* Variables and functions */

__attribute__((used)) static void i40iw_setup_termhdr(struct i40iw_sc_qp *qp,
				struct i40iw_terminate_hdr *hdr,
				enum i40iw_flush_opcode opcode,
				u8 layer_etype,
				u8 err)
{
	qp->flush_code = opcode;
	hdr->layer_etype = layer_etype;
	hdr->error_code = err;
}