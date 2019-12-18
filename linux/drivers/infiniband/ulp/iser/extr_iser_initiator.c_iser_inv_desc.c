#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ mr_valid; TYPE_2__* sig_mr; TYPE_1__* mr; } ;
struct iser_fr_desc {TYPE_3__ rsc; scalar_t__ sig_protected; } ;
struct TYPE_5__ {scalar_t__ rkey; } ;
struct TYPE_4__ {scalar_t__ rkey; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iser_err (char*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int
iser_inv_desc(struct iser_fr_desc *desc, u32 rkey)
{
	if (unlikely((!desc->sig_protected && rkey != desc->rsc.mr->rkey) ||
		     (desc->sig_protected && rkey != desc->rsc.sig_mr->rkey))) {
		iser_err("Bogus remote invalidation for rkey %#x\n", rkey);
		return -EINVAL;
	}

	desc->rsc.mr_valid = 0;

	return 0;
}