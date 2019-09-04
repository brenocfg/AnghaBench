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
typedef  int u32 ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SB_ADDR ; 
 int SB_BUSY ; 
 int /*<<< orphan*/  SB_BYTE_ENABLE ; 
 int /*<<< orphan*/  SB_DATA ; 
 int /*<<< orphan*/  SB_DEST ; 
 int SB_DEST_DPLL ; 
 int /*<<< orphan*/  SB_OPCODE ; 
 int SB_OPCODE_READ ; 
 int /*<<< orphan*/  SB_PCKT ; 
 int SET_FIELD (int,int /*<<< orphan*/ ) ; 
 int wait_for (int,int) ; 

int cdv_sb_read(struct drm_device *dev, u32 reg, u32 *val)
{
	int ret;

	ret = wait_for((REG_READ(SB_PCKT) & SB_BUSY) == 0, 1000);
	if (ret) {
		DRM_ERROR("timeout waiting for SB to idle before read\n");
		return ret;
	}

	REG_WRITE(SB_ADDR, reg);
	REG_WRITE(SB_PCKT,
		   SET_FIELD(SB_OPCODE_READ, SB_OPCODE) |
		   SET_FIELD(SB_DEST_DPLL, SB_DEST) |
		   SET_FIELD(0xf, SB_BYTE_ENABLE));

	ret = wait_for((REG_READ(SB_PCKT) & SB_BUSY) == 0, 1000);
	if (ret) {
		DRM_ERROR("timeout waiting for SB to idle after read\n");
		return ret;
	}

	*val = REG_READ(SB_DATA);

	return 0;
}