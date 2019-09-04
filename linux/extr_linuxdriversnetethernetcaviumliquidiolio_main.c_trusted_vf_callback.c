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
typedef  int /*<<< orphan*/  u32 ;
struct octeon_soft_command {scalar_t__ ctxptr; } ;
struct octeon_device {int dummy; } ;
struct lio_trusted_vf_ctx {int /*<<< orphan*/  complete; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void trusted_vf_callback(struct octeon_device *oct_dev,
				u32 status, void *ptr)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)ptr;
	struct lio_trusted_vf_ctx *ctx;

	ctx = (struct lio_trusted_vf_ctx *)sc->ctxptr;
	ctx->status = status;

	complete(&ctx->complete);
}