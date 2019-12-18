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
struct bnx2x_fastpath {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int bnx2x_vf_ustorm_prods_offset(struct bnx2x *bp,
					       struct bnx2x_fastpath *fp) {return 0; }