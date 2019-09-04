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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int bnx2x_vfpf_update_vlan(struct bnx2x *bp, u16 vid, u8 vf_qid, bool add) {return 0; }