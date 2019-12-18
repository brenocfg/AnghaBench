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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
#define  B43legacy_ANTENNA0 129 
#define  B43legacy_ANTENNA1 128 
 int /*<<< orphan*/  B43legacy_TX4_PHY_ANT0 ; 
 int /*<<< orphan*/  B43legacy_TX4_PHY_ANT1 ; 
 int /*<<< orphan*/  B43legacy_TX4_PHY_ANTLAST ; 

__attribute__((used)) static u16 b43legacy_antenna_to_phyctl(int antenna)
{
	switch (antenna) {
	case B43legacy_ANTENNA0:
		return B43legacy_TX4_PHY_ANT0;
	case B43legacy_ANTENNA1:
		return B43legacy_TX4_PHY_ANT1;
	}
	return B43legacy_TX4_PHY_ANTLAST;
}