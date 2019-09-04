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
struct sun4i_req_ctx {int /*<<< orphan*/ * hash; scalar_t__ byte_count; scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct md5_state {int /*<<< orphan*/ * hash; int /*<<< orphan*/  block; scalar_t__ byte_count; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_H0 ; 
 int /*<<< orphan*/  SHA1_H1 ; 
 int /*<<< orphan*/  SHA1_H2 ; 
 int /*<<< orphan*/  SHA1_H3 ; 
 struct sun4i_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int sun4i_hash_export_md5(struct ahash_request *areq, void *out)
{
	struct sun4i_req_ctx *op = ahash_request_ctx(areq);
	struct md5_state *octx = out;
	int i;

	octx->byte_count = op->byte_count + op->len;

	memcpy(octx->block, op->buf, op->len);

	if (op->byte_count) {
		for (i = 0; i < 4; i++)
			octx->hash[i] = op->hash[i];
	} else {
		octx->hash[0] = SHA1_H0;
		octx->hash[1] = SHA1_H1;
		octx->hash[2] = SHA1_H2;
		octx->hash[3] = SHA1_H3;
	}

	return 0;
}