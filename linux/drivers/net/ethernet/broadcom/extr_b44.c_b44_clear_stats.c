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
struct b44 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_MIB_CTRL ; 
 unsigned long B44_RX_GOOD_O ; 
 unsigned long B44_RX_NPAUSE ; 
 unsigned long B44_TX_GOOD_O ; 
 unsigned long B44_TX_PAUSE ; 
 int /*<<< orphan*/  MIB_CTRL_CLR_ON_READ ; 
 int /*<<< orphan*/  br32 (struct b44*,unsigned long) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b44_clear_stats(struct b44 *bp)
{
	unsigned long reg;

	bw32(bp, B44_MIB_CTRL, MIB_CTRL_CLR_ON_READ);
	for (reg = B44_TX_GOOD_O; reg <= B44_TX_PAUSE; reg += 4UL)
		br32(bp, reg);
	for (reg = B44_RX_GOOD_O; reg <= B44_RX_NPAUSE; reg += 4UL)
		br32(bp, reg);
}