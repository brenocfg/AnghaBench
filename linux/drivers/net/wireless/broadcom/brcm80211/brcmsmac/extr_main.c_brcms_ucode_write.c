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
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u32 ;
struct brcms_hardware {int /*<<< orphan*/  unit; struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int OBJADDR_AUTO_INC ; 
 int OBJADDR_UCM_SEL ; 
 int /*<<< orphan*/  bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_dbg_info (struct bcma_device*,char*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  objaddr ; 
 int /*<<< orphan*/  objdata ; 

__attribute__((used)) static void brcms_ucode_write(struct brcms_hardware *wlc_hw,
			      const __le32 ucode[], const size_t nbytes)
{
	struct bcma_device *core = wlc_hw->d11core;
	uint i;
	uint count;

	brcms_dbg_info(wlc_hw->d11core, "wl%d\n", wlc_hw->unit);

	count = (nbytes / sizeof(u32));

	bcma_write32(core, D11REGOFFS(objaddr),
		     OBJADDR_AUTO_INC | OBJADDR_UCM_SEL);
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	for (i = 0; i < count; i++)
		bcma_write32(core, D11REGOFFS(objdata), le32_to_cpu(ucode[i]));

}