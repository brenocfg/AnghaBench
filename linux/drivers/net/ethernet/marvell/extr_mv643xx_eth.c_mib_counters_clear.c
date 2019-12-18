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
struct mv643xx_eth_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DISCARD_FRAME_CNT ; 
 int /*<<< orphan*/  RX_OVERRUN_FRAME_CNT ; 
 int /*<<< orphan*/  mib_read (struct mv643xx_eth_private*,int) ; 
 int /*<<< orphan*/  rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mib_counters_clear(struct mv643xx_eth_private *mp)
{
	int i;

	for (i = 0; i < 0x80; i += 4)
		mib_read(mp, i);

	/* Clear non MIB hw counters also */
	rdlp(mp, RX_DISCARD_FRAME_CNT);
	rdlp(mp, RX_OVERRUN_FRAME_CNT);
}