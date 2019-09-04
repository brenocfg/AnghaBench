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
struct pd_uinfo {TYPE_3__* sr_va; } ;
struct TYPE_4__ {scalar_t__ hash_alg; } ;
struct TYPE_5__ {TYPE_1__ bf; } ;
struct dynamic_sa_ctl {TYPE_2__ sa_command_0; } ;
struct crypto4xx_ctx {scalar_t__ sa_in; } ;
struct TYPE_6__ {int /*<<< orphan*/  save_digest; } ;

/* Variables and functions */
 scalar_t__ SA_HASH_ALG_SHA1 ; 
 int /*<<< orphan*/  SA_HASH_ALG_SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto4xx_copy_digest_to_dst(void *dst,
					struct pd_uinfo *pd_uinfo,
					struct crypto4xx_ctx *ctx)
{
	struct dynamic_sa_ctl *sa = (struct dynamic_sa_ctl *) ctx->sa_in;

	if (sa->sa_command_0.bf.hash_alg == SA_HASH_ALG_SHA1) {
		memcpy(dst, pd_uinfo->sr_va->save_digest,
		       SA_HASH_ALG_SHA1_DIGEST_SIZE);
	}
}