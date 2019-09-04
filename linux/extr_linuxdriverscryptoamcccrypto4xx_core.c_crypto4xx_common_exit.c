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
struct crypto4xx_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto4xx_free_sa (struct crypto4xx_ctx*) ; 

__attribute__((used)) static void crypto4xx_common_exit(struct crypto4xx_ctx *ctx)
{
	crypto4xx_free_sa(ctx);
}