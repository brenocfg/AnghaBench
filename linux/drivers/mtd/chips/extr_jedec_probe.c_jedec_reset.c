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
struct map_info {int dummy; } ;
struct cfi_private {int /*<<< orphan*/  device_type; scalar_t__ addr_unlock1; scalar_t__ addr_unlock2; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfi_send_gen_cmd (int,scalar_t__,int /*<<< orphan*/ ,struct map_info*,struct cfi_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void jedec_reset(u32 base, struct map_info *map, struct cfi_private *cfi)
{
	/* Reset */

	/* after checking the datasheets for SST, MACRONIX and ATMEL
	 * (oh and incidentaly the jedec spec - 3.5.3.3) the reset
	 * sequence is *supposed* to be 0xaa at 0x5555, 0x55 at
	 * 0x2aaa, 0xF0 at 0x5555 this will not affect the AMD chips
	 * as they will ignore the writes and don't care what address
	 * the F0 is written to */
	if (cfi->addr_unlock1) {
		pr_debug( "reset unlock called %x %x \n",
		       cfi->addr_unlock1,cfi->addr_unlock2);
		cfi_send_gen_cmd(0xaa, cfi->addr_unlock1, base, map, cfi, cfi->device_type, NULL);
		cfi_send_gen_cmd(0x55, cfi->addr_unlock2, base, map, cfi, cfi->device_type, NULL);
	}

	cfi_send_gen_cmd(0xF0, cfi->addr_unlock1, base, map, cfi, cfi->device_type, NULL);
	/* Some misdesigned Intel chips do not respond for 0xF0 for a reset,
	 * so ensure we're in read mode.  Send both the Intel and the AMD command
	 * for this.  Intel uses 0xff for this, AMD uses 0xff for NOP, so
	 * this should be safe.
	 */
	cfi_send_gen_cmd(0xFF, 0, base, map, cfi, cfi->device_type, NULL);
	/* FIXME - should have reset delay before continuing */
}