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
struct rvu {int dummy; } ;
struct msg_rsp {int dummy; } ;
struct hwctx_disable_req {int dummy; } ;

/* Variables and functions */
 int nix_lf_hwctx_disable (struct rvu*,struct hwctx_disable_req*) ; 

int rvu_mbox_handler_nix_hwctx_disable(struct rvu *rvu,
				       struct hwctx_disable_req *req,
				       struct msg_rsp *rsp)
{
	return nix_lf_hwctx_disable(rvu, req);
}