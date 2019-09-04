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
struct crypto_engine {int dummy; } ;
struct akcipher_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int crypto_transfer_request_to_engine (struct crypto_engine*,int /*<<< orphan*/ *) ; 

int crypto_transfer_akcipher_request_to_engine(struct crypto_engine *engine,
					       struct akcipher_request *req)
{
	return crypto_transfer_request_to_engine(engine, &req->base);
}