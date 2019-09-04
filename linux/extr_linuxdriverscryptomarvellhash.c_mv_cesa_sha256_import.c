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
struct sha256_state {int /*<<< orphan*/  buf; int /*<<< orphan*/  count; int /*<<< orphan*/  state; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int mv_cesa_ahash_import (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_sha256_import(struct ahash_request *req, const void *in)
{
	const struct sha256_state *in_state = in;

	return mv_cesa_ahash_import(req, in_state->state, in_state->count,
				    in_state->buf);
}