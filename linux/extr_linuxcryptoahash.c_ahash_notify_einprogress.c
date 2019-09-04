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
struct ahash_request_priv {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct ahash_request {struct ahash_request_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ahash_notify_einprogress(struct ahash_request *req)
{
	struct ahash_request_priv *priv = req->priv;
	struct crypto_async_request oreq;

	oreq.data = priv->data;

	priv->complete(&oreq, -EINPROGRESS);
}