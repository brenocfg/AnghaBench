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
struct decon_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECON_SHADOWCON ; 
 int /*<<< orphan*/  SHADOWCON_PROTECT_MASK ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decon_shadow_protect(struct decon_context *ctx, bool protect)
{
	decon_set_bits(ctx, DECON_SHADOWCON, SHADOWCON_PROTECT_MASK,
		       protect ? ~0 : 0);
}