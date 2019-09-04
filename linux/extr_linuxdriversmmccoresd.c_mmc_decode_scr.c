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
struct sd_scr {int sda_vsn; int bus_widths; int sda_spec3; int cmds; } ;
struct mmc_card {int erased_byte; int /*<<< orphan*/  host; int /*<<< orphan*/ * raw_scr; struct sd_scr scr; } ;

/* Variables and functions */
 int EINVAL ; 
 int SCR_SPEC_VER_2 ; 
 int UNSTUFF_BITS (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mmc_decode_scr(struct mmc_card *card)
{
	struct sd_scr *scr = &card->scr;
	unsigned int scr_struct;
	u32 resp[4];

	resp[3] = card->raw_scr[1];
	resp[2] = card->raw_scr[0];

	scr_struct = UNSTUFF_BITS(resp, 60, 4);
	if (scr_struct != 0) {
		pr_err("%s: unrecognised SCR structure version %d\n",
			mmc_hostname(card->host), scr_struct);
		return -EINVAL;
	}

	scr->sda_vsn = UNSTUFF_BITS(resp, 56, 4);
	scr->bus_widths = UNSTUFF_BITS(resp, 48, 4);
	if (scr->sda_vsn == SCR_SPEC_VER_2)
		/* Check if Physical Layer Spec v3.0 is supported */
		scr->sda_spec3 = UNSTUFF_BITS(resp, 47, 1);

	if (UNSTUFF_BITS(resp, 55, 1))
		card->erased_byte = 0xFF;
	else
		card->erased_byte = 0x0;

	if (scr->sda_spec3)
		scr->cmds = UNSTUFF_BITS(resp, 32, 2);
	return 0;
}