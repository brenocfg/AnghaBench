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

/* Variables and functions */
 int /*<<< orphan*/  QE_CR_PROTOCOL_UNSPECIFIED ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_INVALID ; 
 int /*<<< orphan*/  QE_IMMAP_SIZE ; 
 int /*<<< orphan*/  QE_RESET ; 
 int /*<<< orphan*/  get_qe_base () ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * qe_immr ; 
 int /*<<< orphan*/  qe_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_muram_init () ; 
 scalar_t__ qe_sdma_init () ; 
 int /*<<< orphan*/  qe_snums_init () ; 

void qe_reset(void)
{
	if (qe_immr == NULL)
		qe_immr = ioremap(get_qe_base(), QE_IMMAP_SIZE);

	qe_snums_init();

	qe_issue_cmd(QE_RESET, QE_CR_SUBBLOCK_INVALID,
		     QE_CR_PROTOCOL_UNSPECIFIED, 0);

	/* Reclaim the MURAM memory for our use. */
	qe_muram_init();

	if (qe_sdma_init())
		panic("sdma init failed!");
}