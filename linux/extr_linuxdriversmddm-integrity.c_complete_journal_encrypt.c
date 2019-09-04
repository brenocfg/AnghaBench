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
struct journal_completion {TYPE_1__* ic; } ;
struct crypto_async_request {struct journal_completion* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  crypto_backoff; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_journal_op (struct journal_completion*) ; 
 int /*<<< orphan*/  dm_integrity_io_error (TYPE_1__*,char*,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void complete_journal_encrypt(struct crypto_async_request *req, int err)
{
	struct journal_completion *comp = req->data;
	if (unlikely(err)) {
		if (likely(err == -EINPROGRESS)) {
			complete(&comp->ic->crypto_backoff);
			return;
		}
		dm_integrity_io_error(comp->ic, "asynchronous encrypt", err);
	}
	complete_journal_op(comp);
}