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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tpm_space {int /*<<< orphan*/ * session_buf; int /*<<< orphan*/ * context_buf; int /*<<< orphan*/  session_tbl; int /*<<< orphan*/  context_tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/ * session_buf; int /*<<< orphan*/ * context_buf; int /*<<< orphan*/  session_tbl; int /*<<< orphan*/  context_tbl; } ;
struct tpm_chip {TYPE_1__ work_space; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tpm2_flush_space (struct tpm_chip*) ; 
 int tpm2_load_space (struct tpm_chip*) ; 
 int tpm2_map_command (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int tpm2_prepare_space(struct tpm_chip *chip, struct tpm_space *space, u32 cc,
		       u8 *cmd)
{
	int rc;

	if (!space)
		return 0;

	memcpy(&chip->work_space.context_tbl, &space->context_tbl,
	       sizeof(space->context_tbl));
	memcpy(&chip->work_space.session_tbl, &space->session_tbl,
	       sizeof(space->session_tbl));
	memcpy(chip->work_space.context_buf, space->context_buf, PAGE_SIZE);
	memcpy(chip->work_space.session_buf, space->session_buf, PAGE_SIZE);

	rc = tpm2_load_space(chip);
	if (rc) {
		tpm2_flush_space(chip);
		return rc;
	}

	rc = tpm2_map_command(chip, cc, cmd);
	if (rc) {
		tpm2_flush_space(chip);
		return rc;
	}

	return 0;
}