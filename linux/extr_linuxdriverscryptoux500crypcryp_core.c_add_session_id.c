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
struct cryp_ctx {int /*<<< orphan*/  session_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_id ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_session_id(struct cryp_ctx *ctx)
{
	/*
	 * We never want 0 to be a valid value, since this is the default value
	 * for the software context.
	 */
	if (unlikely(atomic_inc_and_test(&session_id)))
		atomic_inc(&session_id);

	ctx->session_id = atomic_read(&session_id);
}