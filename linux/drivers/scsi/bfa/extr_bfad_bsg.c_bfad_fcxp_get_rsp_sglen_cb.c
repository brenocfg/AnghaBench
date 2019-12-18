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
typedef  int /*<<< orphan*/  u32 ;
struct bfad_fcxp {struct bfa_sge_s* rsp_sge; } ;
struct bfa_sge_s {int /*<<< orphan*/  sg_len; } ;

/* Variables and functions */

u32
bfad_fcxp_get_rsp_sglen_cb(void *bfad_fcxp, int sgeid)
{
	struct bfad_fcxp	*drv_fcxp = bfad_fcxp;
	struct bfa_sge_s	*sge;

	sge = drv_fcxp->rsp_sge + sgeid;
	return sge->sg_len;
}