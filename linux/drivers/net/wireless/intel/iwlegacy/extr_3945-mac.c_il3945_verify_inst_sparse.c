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
typedef  scalar_t__ u32 ;
struct il_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,scalar_t__) ; 
 int EIO ; 
 int /*<<< orphan*/  HBUS_TARG_MEM_RADDR ; 
 int /*<<< orphan*/  HBUS_TARG_MEM_RDAT ; 
 scalar_t__ IL39_RTC_INST_LOWER_BOUND ; 
 int /*<<< orphan*/  IL_ERR (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
il3945_verify_inst_sparse(struct il_priv *il, __le32 * image, u32 len)
{
	u32 val;
	int rc = 0;
	u32 errcnt = 0;
	u32 i;

	D_INFO("ucode inst image size is %u\n", len);

	for (i = 0; i < len; i += 100, image += 100 / sizeof(u32)) {
		/* read data comes through single port, auto-incr addr */
		/* NOTE: Use the debugless read so we don't flood kernel log
		 * if IL_DL_IO is set */
		il_wr(il, HBUS_TARG_MEM_RADDR, i + IL39_RTC_INST_LOWER_BOUND);
		val = _il_rd(il, HBUS_TARG_MEM_RDAT);
		if (val != le32_to_cpu(*image)) {
#if 0				/* Enable this if you want to see details */
			IL_ERR("uCode INST section is invalid at "
			       "offset 0x%x, is 0x%x, s/b 0x%x\n", i, val,
			       *image);
#endif
			rc = -EIO;
			errcnt++;
			if (errcnt >= 3)
				break;
		}
	}

	return rc;
}