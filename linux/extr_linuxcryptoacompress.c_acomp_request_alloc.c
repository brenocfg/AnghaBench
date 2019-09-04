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
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct crypto_acomp {int dummy; } ;
struct acomp_req {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cra_type; } ;

/* Variables and functions */
 struct acomp_req* __acomp_request_alloc (struct crypto_acomp*) ; 
 struct acomp_req* crypto_acomp_scomp_alloc_ctx (struct acomp_req*) ; 
 struct crypto_tfm* crypto_acomp_tfm (struct crypto_acomp*) ; 
 int /*<<< orphan*/  crypto_acomp_type ; 

struct acomp_req *acomp_request_alloc(struct crypto_acomp *acomp)
{
	struct crypto_tfm *tfm = crypto_acomp_tfm(acomp);
	struct acomp_req *req;

	req = __acomp_request_alloc(acomp);
	if (req && (tfm->__crt_alg->cra_type != &crypto_acomp_type))
		return crypto_acomp_scomp_alloc_ctx(req);

	return req;
}