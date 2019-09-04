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
struct sock {int dummy; } ;
struct af_alg_async_req {unsigned int areqlen; scalar_t__ tsgl_entries; int /*<<< orphan*/ * tsgl; int /*<<< orphan*/  rsgl_list; int /*<<< orphan*/ * last_rsgl; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct af_alg_async_req* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct af_alg_async_req* sock_kmalloc (struct sock*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct af_alg_async_req *af_alg_alloc_areq(struct sock *sk,
					   unsigned int areqlen)
{
	struct af_alg_async_req *areq = sock_kmalloc(sk, areqlen, GFP_KERNEL);

	if (unlikely(!areq))
		return ERR_PTR(-ENOMEM);

	areq->areqlen = areqlen;
	areq->sk = sk;
	areq->last_rsgl = NULL;
	INIT_LIST_HEAD(&areq->rsgl_list);
	areq->tsgl = NULL;
	areq->tsgl_entries = 0;

	return areq;
}