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
struct crypto_ahash {int (* update ) (struct ahash_request*) ;} ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  ahash_def_finup_done1 ; 
 int ahash_def_finup_finish1 (struct ahash_request*,int) ; 
 int ahash_save_req (struct ahash_request*,int /*<<< orphan*/ ) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int stub1 (struct ahash_request*) ; 

__attribute__((used)) static int ahash_def_finup(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	int err;

	err = ahash_save_req(req, ahash_def_finup_done1);
	if (err)
		return err;

	err = tfm->update(req);
	if (err == -EINPROGRESS || err == -EBUSY)
		return err;

	return ahash_def_finup_finish1(req, err);
}