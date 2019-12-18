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
struct TYPE_4__ {int /*<<< orphan*/  (* clear_pending ) (TYPE_2__*) ;} ;
struct TYPE_3__ {TYPE_2__ raw; } ;
struct bnx2x_virtf {TYPE_1__ rss_conf_obj; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void bnx2x_vf_handle_rss_update_eqe(struct bnx2x *bp,
					   struct bnx2x_virtf *vf)
{
	vf->rss_conf_obj.raw.clear_pending(&vf->rss_conf_obj.raw);
}