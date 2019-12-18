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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pucan_std_filter {int /*<<< orphan*/  mask; int /*<<< orphan*/  idx; } ;
struct peak_canfd_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUCAN_CMD_SET_STD_FILTER ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct pucan_std_filter* pucan_add_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pucan_init_cmd (struct peak_canfd_priv*) ; 
 int pucan_write_cmd (struct peak_canfd_priv*) ; 

__attribute__((used)) static int pucan_set_std_filter(struct peak_canfd_priv *priv, u8 row, u32 mask)
{
	struct pucan_std_filter *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_SET_STD_FILTER);

	/* all the 11-bits CAN ID values are represented by one bit in a
	 * 64 rows array of 32 bits: the upper 6 bits of the CAN ID select the
	 * row while the lowest 5 bits select the bit in that row.
	 *
	 * bit	filter
	 * 1	passed
	 * 0	discarded
	 */

	/* select the row */
	cmd->idx = row;

	/* set/unset bits in the row */
	cmd->mask = cpu_to_le32(mask);

	return pucan_write_cmd(priv);
}