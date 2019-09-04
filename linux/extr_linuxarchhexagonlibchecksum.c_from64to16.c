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
typedef  int u64 ;

/* Variables and functions */
 int HEXAGON_P_vrmpyh_PP (int,int /*<<< orphan*/ ) ; 
 scalar_t__ VR_CARRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int VR_NEGATE (int,int,int,int) ; 
 int /*<<< orphan*/  VR_SELECT (int,int,int,int) ; 

__attribute__((used)) static inline unsigned short from64to16(u64 x)
{
	u64 sum;

	sum = HEXAGON_P_vrmpyh_PP(x^VR_NEGATE(1, 1, 1, 1),
			     VR_SELECT(1, 1, 1, 1));
	sum += VR_CARRY(0, 0, 1, 0);
	sum = HEXAGON_P_vrmpyh_PP(sum, VR_SELECT(0, 0, 1, 1));

	return 0xFFFF & sum;
}