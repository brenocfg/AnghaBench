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
typedef  int u32 ;
struct brcmf_pciedev_info {TYPE_1__* ci; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int ramsize; } ;

/* Variables and functions */
 scalar_t__ BRCMF_RAMSIZE_MAGIC ; 
 int BRCMF_RAMSIZE_OFFSET ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ le32_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
brcmf_pcie_adjust_ramsize(struct brcmf_pciedev_info *devinfo, u8 *data,
			  u32 data_len)
{
	__le32 *field;
	u32 newsize;

	if (data_len < BRCMF_RAMSIZE_OFFSET + 8)
		return;

	field = (__le32 *)&data[BRCMF_RAMSIZE_OFFSET];
	if (le32_to_cpup(field) != BRCMF_RAMSIZE_MAGIC)
		return;
	field++;
	newsize = le32_to_cpup(field);

	brcmf_dbg(PCIE, "Found ramsize info in FW, adjusting to 0x%x\n",
		  newsize);
	devinfo->ci->ramsize = newsize;
}