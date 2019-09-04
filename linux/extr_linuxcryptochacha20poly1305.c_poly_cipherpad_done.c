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
struct crypto_async_request {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_done_continue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poly_tail ; 

__attribute__((used)) static void poly_cipherpad_done(struct crypto_async_request *areq, int err)
{
	async_done_continue(areq->data, err, poly_tail);
}