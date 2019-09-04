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
typedef  int uint8_t ;
typedef  enum transmitter { ____Placeholder_transmitter } transmitter ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  TRANSMITTER_TRAVIS_LCD 134 
#define  TRANSMITTER_UNIPHY_A 133 
#define  TRANSMITTER_UNIPHY_B 132 
#define  TRANSMITTER_UNIPHY_C 131 
#define  TRANSMITTER_UNIPHY_D 130 
#define  TRANSMITTER_UNIPHY_E 129 
#define  TRANSMITTER_UNIPHY_F 128 

uint8_t dal_cmd_table_helper_transmitter_bp_to_atom(
	enum transmitter t)
{
	switch (t) {
	case TRANSMITTER_UNIPHY_A:
	case TRANSMITTER_UNIPHY_B:
	case TRANSMITTER_TRAVIS_LCD:
		return 0;
	case TRANSMITTER_UNIPHY_C:
	case TRANSMITTER_UNIPHY_D:
		return 1;
	case TRANSMITTER_UNIPHY_E:
	case TRANSMITTER_UNIPHY_F:
		return 2;
	default:
		/* Invalid Transmitter Type! */
		BREAK_TO_DEBUGGER();
		return 0;
	}
}