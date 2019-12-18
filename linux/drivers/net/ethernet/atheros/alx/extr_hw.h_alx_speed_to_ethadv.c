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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_1000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Half ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 

__attribute__((used)) static inline u32 alx_speed_to_ethadv(int speed, u8 duplex)
{
	if (speed == SPEED_1000 && duplex == DUPLEX_FULL)
		return ADVERTISED_1000baseT_Full;
	if (speed == SPEED_100 && duplex == DUPLEX_FULL)
		return ADVERTISED_100baseT_Full;
	if (speed == SPEED_100 && duplex== DUPLEX_HALF)
		return ADVERTISED_100baseT_Half;
	if (speed == SPEED_10 && duplex == DUPLEX_FULL)
		return ADVERTISED_10baseT_Full;
	if (speed == SPEED_10 && duplex == DUPLEX_HALF)
		return ADVERTISED_10baseT_Half;
	return 0;
}