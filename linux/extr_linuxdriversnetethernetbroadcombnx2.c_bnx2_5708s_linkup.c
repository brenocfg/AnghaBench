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
typedef  int u32 ;
struct bnx2 {int link_up; int /*<<< orphan*/  duplex; int /*<<< orphan*/  line_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM5708S_1000X_STAT1 ; 
 int BCM5708S_1000X_STAT1_FD ; 
#define  BCM5708S_1000X_STAT1_SPEED_10 131 
#define  BCM5708S_1000X_STAT1_SPEED_100 130 
#define  BCM5708S_1000X_STAT1_SPEED_1G 129 
#define  BCM5708S_1000X_STAT1_SPEED_2G5 128 
 int BCM5708S_1000X_STAT1_SPEED_MASK ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
bnx2_5708s_linkup(struct bnx2 *bp)
{
	u32 val;

	bp->link_up = 1;
	bnx2_read_phy(bp, BCM5708S_1000X_STAT1, &val);
	switch (val & BCM5708S_1000X_STAT1_SPEED_MASK) {
		case BCM5708S_1000X_STAT1_SPEED_10:
			bp->line_speed = SPEED_10;
			break;
		case BCM5708S_1000X_STAT1_SPEED_100:
			bp->line_speed = SPEED_100;
			break;
		case BCM5708S_1000X_STAT1_SPEED_1G:
			bp->line_speed = SPEED_1000;
			break;
		case BCM5708S_1000X_STAT1_SPEED_2G5:
			bp->line_speed = SPEED_2500;
			break;
	}
	if (val & BCM5708S_1000X_STAT1_FD)
		bp->duplex = DUPLEX_FULL;
	else
		bp->duplex = DUPLEX_HALF;

	return 0;
}