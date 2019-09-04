#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ mr_valid; TYPE_1__* mr; } ;
struct iser_fr_desc {TYPE_4__* pi_ctx; TYPE_2__ rsc; } ;
struct TYPE_8__ {scalar_t__ sig_mr_valid; TYPE_3__* sig_mr; } ;
struct TYPE_7__ {scalar_t__ rkey; } ;
struct TYPE_5__ {scalar_t__ rkey; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline void
iser_inv_desc(struct iser_fr_desc *desc, u32 rkey)
{
	if (likely(rkey == desc->rsc.mr->rkey))
		desc->rsc.mr_valid = 0;
	else if (likely(rkey == desc->pi_ctx->sig_mr->rkey))
		desc->pi_ctx->sig_mr_valid = 0;
}