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
struct skcipher_request {int dummy; } ;
struct journal_completion {TYPE_1__* ic; } ;
struct TYPE_2__ {int /*<<< orphan*/  crypto_backoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  complete_journal_encrypt ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  dm_integrity_io_error (TYPE_1__*,char*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct journal_completion*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool do_crypt(bool encrypt, struct skcipher_request *req, struct journal_completion *comp)
{
	int r;
	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      complete_journal_encrypt, comp);
	if (likely(encrypt))
		r = crypto_skcipher_encrypt(req);
	else
		r = crypto_skcipher_decrypt(req);
	if (likely(!r))
		return false;
	if (likely(r == -EINPROGRESS))
		return true;
	if (likely(r == -EBUSY)) {
		wait_for_completion(&comp->ic->crypto_backoff);
		reinit_completion(&comp->ic->crypto_backoff);
		return true;
	}
	dm_integrity_io_error(comp->ic, "encrypt", r);
	return false;
}