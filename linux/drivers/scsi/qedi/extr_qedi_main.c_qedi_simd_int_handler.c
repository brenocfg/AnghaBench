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
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_WARN (int /*<<< orphan*/ *,char*,struct qedi_ctx*) ; 

__attribute__((used)) static void qedi_simd_int_handler(void *cookie)
{
	/* Cookie is qedi_ctx struct */
	struct qedi_ctx *qedi = (struct qedi_ctx *)cookie;

	QEDI_WARN(&qedi->dbg_ctx, "qedi=%p.\n", qedi);
}