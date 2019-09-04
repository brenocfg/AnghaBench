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
struct spu_hw {scalar_t__ spu_type; } ;
struct TYPE_3__ {scalar_t__ alg; scalar_t__ mode; } ;
struct iproc_ctx_s {TYPE_1__ auth; } ;
struct TYPE_4__ {struct spu_hw spu; } ;

/* Variables and functions */
 scalar_t__ HASH_ALG_AES ; 
 scalar_t__ HASH_MODE_XCBC ; 
 scalar_t__ SPU_TYPE_SPU2 ; 
 TYPE_2__ iproc_priv ; 

bool spu_no_incr_hash(struct iproc_ctx_s *ctx)
{
	struct spu_hw *spu = &iproc_priv.spu;

	if (spu->spu_type == SPU_TYPE_SPU2)
		return true;

	if ((ctx->auth.alg == HASH_ALG_AES) &&
	    (ctx->auth.mode == HASH_MODE_XCBC))
		return true;

	/* Otherwise, incremental hashing is supported */
	return false;
}