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
struct crypto_tfm {TYPE_2__* __crt_alg; } ;
struct TYPE_3__ {int /*<<< orphan*/  exit; } ;
struct crypto_acomp {TYPE_1__ base; int /*<<< orphan*/  reqsize; int /*<<< orphan*/  dst_free; int /*<<< orphan*/  decompress; int /*<<< orphan*/  compress; } ;
struct acomp_alg {int (* init ) (struct crypto_acomp*) ;scalar_t__ exit; int /*<<< orphan*/  reqsize; int /*<<< orphan*/  dst_free; int /*<<< orphan*/  decompress; int /*<<< orphan*/  compress; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cra_type; } ;

/* Variables and functions */
 struct crypto_acomp* __crypto_acomp_tfm (struct crypto_tfm*) ; 
 struct acomp_alg* crypto_acomp_alg (struct crypto_acomp*) ; 
 int /*<<< orphan*/  crypto_acomp_exit_tfm ; 
 int /*<<< orphan*/  crypto_acomp_type ; 
 int crypto_init_scomp_ops_async (struct crypto_tfm*) ; 
 int stub1 (struct crypto_acomp*) ; 

__attribute__((used)) static int crypto_acomp_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_acomp *acomp = __crypto_acomp_tfm(tfm);
	struct acomp_alg *alg = crypto_acomp_alg(acomp);

	if (tfm->__crt_alg->cra_type != &crypto_acomp_type)
		return crypto_init_scomp_ops_async(tfm);

	acomp->compress = alg->compress;
	acomp->decompress = alg->decompress;
	acomp->dst_free = alg->dst_free;
	acomp->reqsize = alg->reqsize;

	if (alg->exit)
		acomp->base.exit = crypto_acomp_exit_tfm;

	if (alg->init)
		return alg->init(acomp);

	return 0;
}