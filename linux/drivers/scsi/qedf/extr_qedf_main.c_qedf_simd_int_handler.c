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
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*,struct qedf_ctx*) ; 

__attribute__((used)) static void qedf_simd_int_handler(void *cookie)
{
	/* Cookie is qedf_ctx struct */
	struct qedf_ctx *qedf = (struct qedf_ctx *)cookie;

	QEDF_WARN(&(qedf->dbg_ctx), "qedf=%p.\n", qedf);
}