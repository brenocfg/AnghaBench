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
typedef  int u8 ;
typedef  int u32 ;
struct mxl {int demod; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MXL_HYDRA_DEMOD_SCRAMBLE_CODE_CMD ; 
 int MXL_HYDRA_PLID_CMD_WRITE ; 
 int gold2root (int) ; 
 int send_command (struct mxl*,int,int*) ; 

__attribute__((used)) static int cfg_scrambler(struct mxl *state, u32 gold)
{
	u32 root;
	u8 buf[26] = {
		MXL_HYDRA_PLID_CMD_WRITE, 24,
		0, MXL_HYDRA_DEMOD_SCRAMBLE_CODE_CMD, 0, 0,
		state->demod, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0,
	};

	root = gold2root(gold);

	buf[25] = (root >> 24) & 0xff;
	buf[24] = (root >> 16) & 0xff;
	buf[23] = (root >> 8) & 0xff;
	buf[22] = root & 0xff;

	return send_command(state, sizeof(buf), buf);
}