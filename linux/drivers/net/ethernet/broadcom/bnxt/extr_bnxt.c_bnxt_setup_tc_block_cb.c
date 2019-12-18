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
struct TYPE_2__ {int /*<<< orphan*/  fw_fid; } ;
struct bnxt {TYPE_1__ pf; int /*<<< orphan*/  dev; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 128 
 int /*<<< orphan*/  bnxt_tc_flower_enabled (struct bnxt*) ; 
 int bnxt_tc_setup_flower (struct bnxt*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int bnxt_setup_tc_block_cb(enum tc_setup_type type, void *type_data,
				  void *cb_priv)
{
	struct bnxt *bp = cb_priv;

	if (!bnxt_tc_flower_enabled(bp) ||
	    !tc_cls_can_offload_and_chain0(bp->dev, type_data))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSFLOWER:
		return bnxt_tc_setup_flower(bp, bp->pf.fw_fid, type_data);
	default:
		return -EOPNOTSUPP;
	}
}