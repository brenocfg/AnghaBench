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
typedef  scalar_t__ u32 ;
struct octeon_soft_command {scalar_t__ virtrptr; scalar_t__ ctxptr; } ;
struct octeon_device {int dummy; } ;
struct lio_vf_rep_sc_ctx {int /*<<< orphan*/  complete; } ;
struct lio_vf_rep_resp {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ OCTEON_REQUEST_TIMEOUT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lio_vf_rep_send_sc_complete(struct octeon_device *oct,
			    u32 status, void *ptr)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)ptr;
	struct lio_vf_rep_sc_ctx *ctx =
		(struct lio_vf_rep_sc_ctx *)sc->ctxptr;
	struct lio_vf_rep_resp *resp =
		(struct lio_vf_rep_resp *)sc->virtrptr;

	if (status != OCTEON_REQUEST_TIMEOUT && READ_ONCE(resp->status))
		WRITE_ONCE(resp->status, 0);

	complete(&ctx->complete);
}