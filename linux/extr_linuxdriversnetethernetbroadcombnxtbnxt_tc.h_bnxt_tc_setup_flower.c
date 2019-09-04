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
typedef  int /*<<< orphan*/  u16 ;
struct tc_cls_flower_offload {int dummy; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int bnxt_tc_setup_flower(struct bnxt *bp, u16 src_fid,
				       struct tc_cls_flower_offload *cls_flower)
{
	return -EOPNOTSUPP;
}