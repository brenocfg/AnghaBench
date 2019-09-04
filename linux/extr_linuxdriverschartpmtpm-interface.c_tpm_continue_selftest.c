#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  in; } ;
struct tpm_cmd_t {TYPE_1__ header; } ;
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUE_SELFTEST_RESULT_SIZE ; 
 int /*<<< orphan*/  continue_selftest_header ; 
 int tpm_transmit_cmd (struct tpm_chip*,int /*<<< orphan*/ *,struct tpm_cmd_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tpm_continue_selftest(struct tpm_chip *chip)
{
	int rc;
	struct tpm_cmd_t cmd;

	cmd.header.in = continue_selftest_header;
	rc = tpm_transmit_cmd(chip, NULL, &cmd, CONTINUE_SELFTEST_RESULT_SIZE,
			      0, 0, "continue selftest");
	return rc;
}