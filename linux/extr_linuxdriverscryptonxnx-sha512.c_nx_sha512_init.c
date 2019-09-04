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
struct shash_desc {int dummy; } ;
struct sha512_state {scalar_t__* count; void** state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_H0 ; 
 int /*<<< orphan*/  SHA512_H1 ; 
 int /*<<< orphan*/  SHA512_H2 ; 
 int /*<<< orphan*/  SHA512_H3 ; 
 int /*<<< orphan*/  SHA512_H4 ; 
 int /*<<< orphan*/  SHA512_H5 ; 
 int /*<<< orphan*/  SHA512_H6 ; 
 int /*<<< orphan*/  SHA512_H7 ; 
 void* __cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sha512_state*,int /*<<< orphan*/ ,int) ; 
 struct sha512_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int nx_sha512_init(struct shash_desc *desc)
{
	struct sha512_state *sctx = shash_desc_ctx(desc);

	memset(sctx, 0, sizeof *sctx);

	sctx->state[0] = __cpu_to_be64(SHA512_H0);
	sctx->state[1] = __cpu_to_be64(SHA512_H1);
	sctx->state[2] = __cpu_to_be64(SHA512_H2);
	sctx->state[3] = __cpu_to_be64(SHA512_H3);
	sctx->state[4] = __cpu_to_be64(SHA512_H4);
	sctx->state[5] = __cpu_to_be64(SHA512_H5);
	sctx->state[6] = __cpu_to_be64(SHA512_H6);
	sctx->state[7] = __cpu_to_be64(SHA512_H7);
	sctx->count[0] = 0;

	return 0;
}