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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct stb0899_state {int /*<<< orphan*/  verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ID ; 
 int /*<<< orphan*/  CHIP_REL ; 
 int /*<<< orphan*/  CONVERT32 (scalar_t__,char*) ; 
 int /*<<< orphan*/  DMD_CORE_ID ; 
 int /*<<< orphan*/  DMD_VERSION_ID ; 
 int ENODEV ; 
 int /*<<< orphan*/  FEC_CORE_ID_REG ; 
 int /*<<< orphan*/  FEC_VER_ID_REG ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  STB0899_DEV_ID ; 
 scalar_t__ STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_S2FEC ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_get_dev_id(struct stb0899_state *state)
{
	u8 chip_id, release;
	u16 id;
	u32 demod_ver = 0, fec_ver = 0;
	char demod_str[5] = { 0 };
	char fec_str[5] = { 0 };

	id = stb0899_read_reg(state, STB0899_DEV_ID);
	dprintk(state->verbose, FE_DEBUG, 1, "ID reg=[0x%02x]", id);
	chip_id = STB0899_GETFIELD(CHIP_ID, id);
	release = STB0899_GETFIELD(CHIP_REL, id);

	dprintk(state->verbose, FE_ERROR, 1, "Device ID=[%d], Release=[%d]",
		chip_id, release);

	CONVERT32(STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_CORE_ID), (char *)&demod_str);

	demod_ver = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_VERSION_ID);
	dprintk(state->verbose, FE_ERROR, 1, "Demodulator Core ID=[%s], Version=[%d]", (char *) &demod_str, demod_ver);
	CONVERT32(STB0899_READ_S2REG(STB0899_S2FEC, FEC_CORE_ID_REG), (char *)&fec_str);
	fec_ver = STB0899_READ_S2REG(STB0899_S2FEC, FEC_VER_ID_REG);
	if (! (chip_id > 0)) {
		dprintk(state->verbose, FE_ERROR, 1, "couldn't find a STB 0899");

		return -ENODEV;
	}
	dprintk(state->verbose, FE_ERROR, 1, "FEC Core ID=[%s], Version=[%d]", (char*) &fec_str, fec_ver);

	return 0;
}