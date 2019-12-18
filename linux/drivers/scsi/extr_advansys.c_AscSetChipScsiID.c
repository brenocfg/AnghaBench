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
typedef  int ushort ;
typedef  int uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int ASC_MAX_TID ; 
 int AscGetChipCfgLsw (int /*<<< orphan*/ ) ; 
 int AscGetChipScsiID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipCfgLsw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uchar AscSetChipScsiID(PortAddr iop_base, uchar new_host_id)
{
	ushort cfg_lsw;

	if (AscGetChipScsiID(iop_base) == new_host_id) {
		return (new_host_id);
	}
	cfg_lsw = AscGetChipCfgLsw(iop_base);
	cfg_lsw &= 0xF8FF;
	cfg_lsw |= (ushort)((new_host_id & ASC_MAX_TID) << 8);
	AscSetChipCfgLsw(iop_base, cfg_lsw);
	return (AscGetChipScsiID(iop_base));
}