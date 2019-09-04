#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hwrng {int dummy; } ;
struct buf_data {int /*<<< orphan*/  filled; int /*<<< orphan*/  empty; } ;
struct TYPE_3__ {struct buf_data* bufs; } ;

/* Variables and functions */
 scalar_t__ BUF_PENDING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* rng_ctx ; 
 int /*<<< orphan*/  rng_unmap_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void caam_cleanup(struct hwrng *rng)
{
	int i;
	struct buf_data *bd;

	for (i = 0; i < 2; i++) {
		bd = &rng_ctx->bufs[i];
		if (atomic_read(&bd->empty) == BUF_PENDING)
			wait_for_completion(&bd->filled);
	}

	rng_unmap_ctx(rng_ctx);
}