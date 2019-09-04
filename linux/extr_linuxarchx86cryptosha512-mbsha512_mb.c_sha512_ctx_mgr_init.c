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
struct sha512_ctx_mgr {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sha512_job_mgr_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sha512_ctx_mgr_init(struct sha512_ctx_mgr *mgr)
{
	sha512_job_mgr_init(&mgr->mgr);
}