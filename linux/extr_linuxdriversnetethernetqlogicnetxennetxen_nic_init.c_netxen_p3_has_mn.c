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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_1__ ahw; } ;

/* Variables and functions */
 scalar_t__ NETXEN_DECODE_VERSION (scalar_t__) ; 
 scalar_t__ NETXEN_VERSION_CODE (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_FW_VERSION_OFFSET ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_PEG_TUNE_CAPABILITY ; 
 scalar_t__ NX_PEG_TUNE_MN_PRESENT ; 
 int /*<<< orphan*/  netxen_rom_fast_read (struct netxen_adapter*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
netxen_p3_has_mn(struct netxen_adapter *adapter)
{
	u32 capability, flashed_ver;
	capability = 0;

	/* NX2031 always had MN */
	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return 1;

	netxen_rom_fast_read(adapter,
			NX_FW_VERSION_OFFSET, (int *)&flashed_ver);
	flashed_ver = NETXEN_DECODE_VERSION(flashed_ver);

	if (flashed_ver >= NETXEN_VERSION_CODE(4, 0, 220)) {

		capability = NXRD32(adapter, NX_PEG_TUNE_CAPABILITY);
		if (capability & NX_PEG_TUNE_MN_PRESENT)
			return 1;
	}
	return 0;
}