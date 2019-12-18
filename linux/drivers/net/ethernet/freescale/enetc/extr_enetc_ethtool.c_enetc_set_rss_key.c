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
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_PRSSK (int) ; 
 int ENETC_RSSHASH_KEY_SIZE ; 
 int /*<<< orphan*/  enetc_port_wr (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void enetc_set_rss_key(struct enetc_hw *hw, const u8 *bytes)
{
	int i;

	for (i = 0; i < ENETC_RSSHASH_KEY_SIZE / 4; i++)
		enetc_port_wr(hw, ENETC_PRSSK(i), ((u32 *)bytes)[i]);
}