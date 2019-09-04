#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int fw_is_running; int memcmd; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {TYPE_2__ platform; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dib9000_firmware_download (struct dib9000_state*,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ dib9000_mbx_host_init (struct dib9000_state*,int) ; 
 scalar_t__ dib9000_risc_check_version (struct dib9000_state*) ; 
 int /*<<< orphan*/  dib9000_write_word (struct dib9000_state*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib9000_fw_boot(struct dib9000_state *state, const u8 * codeA, u32 lenA, const u8 * codeB, u32 lenB)
{
	/* Reconfig pool mac ram */
	dib9000_write_word(state, 1225, 0x02);	/* A: 8k C, 4 k D - B: 32k C 6 k D - IRAM 96k */
	dib9000_write_word(state, 1226, 0x05);

	/* Toggles IP crypto to Host APB interface. */
	dib9000_write_word(state, 1542, 1);

	/* Set jump and no jump in the dma box */
	dib9000_write_word(state, 1074, 0);
	dib9000_write_word(state, 1075, 0);

	/* Set MAC as APB Master. */
	dib9000_write_word(state, 1237, 0);

	/* Reset the RISCs */
	if (codeA != NULL)
		dib9000_write_word(state, 1024, 2);
	else
		dib9000_write_word(state, 1024, 15);
	if (codeB != NULL)
		dib9000_write_word(state, 1040, 2);

	if (codeA != NULL)
		dib9000_firmware_download(state, 0, 0x1234, codeA, lenA);
	if (codeB != NULL)
		dib9000_firmware_download(state, 1, 0x1234, codeB, lenB);

	/* Run the RISCs */
	if (codeA != NULL)
		dib9000_write_word(state, 1024, 0);
	if (codeB != NULL)
		dib9000_write_word(state, 1040, 0);

	if (codeA != NULL)
		if (dib9000_mbx_host_init(state, 0) != 0)
			return -EIO;
	if (codeB != NULL)
		if (dib9000_mbx_host_init(state, 1) != 0)
			return -EIO;

	msleep(100);
	state->platform.risc.fw_is_running = 1;

	if (dib9000_risc_check_version(state) != 0)
		return -EINVAL;

	state->platform.risc.memcmd = 0xff;
	return 0;
}