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
struct deflate_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __deflate_exit (struct deflate_ctx*) ; 
 struct deflate_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void deflate_exit(struct crypto_tfm *tfm)
{
	struct deflate_ctx *ctx = crypto_tfm_ctx(tfm);

	__deflate_exit(ctx);
}