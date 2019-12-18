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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct arpc {struct arpc* req; int /*<<< orphan*/  response_received; int /*<<< orphan*/  data; int /*<<< orphan*/  size; int /*<<< orphan*/  type; void* resp; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ARPC_OUT_SIZE_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct arpc*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static struct arpc *arpc_alloc(void *payload, u16 size, u8 type)
{
	struct arpc *rpc;

	if (size + sizeof(*rpc->req) > ARPC_OUT_SIZE_MAX)
		return NULL;

	rpc = kzalloc(sizeof(*rpc), GFP_KERNEL);
	if (!rpc)
		return NULL;

	INIT_LIST_HEAD(&rpc->list);
	rpc->req = kzalloc(sizeof(*rpc->req) + size, GFP_KERNEL);
	if (!rpc->req)
		goto err_free_rpc;

	rpc->resp = kzalloc(sizeof(*rpc->resp), GFP_KERNEL);
	if (!rpc->resp)
		goto err_free_req;

	rpc->req->type = type;
	rpc->req->size = cpu_to_le16(sizeof(*rpc->req) + size);
	memcpy(rpc->req->data, payload, size);

	init_completion(&rpc->response_received);

	return rpc;

err_free_req:
	kfree(rpc->req);
err_free_rpc:
	kfree(rpc);

	return NULL;
}