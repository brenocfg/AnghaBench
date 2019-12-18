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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum transmitter { ____Placeholder_transmitter } transmitter ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_PHY_ID_UNIPHYA ; 
 int /*<<< orphan*/  ATOM_PHY_ID_UNIPHYB ; 
 int /*<<< orphan*/  ATOM_PHY_ID_UNIPHYC ; 
 int /*<<< orphan*/  ATOM_PHY_ID_UNIPHYD ; 
 int /*<<< orphan*/  ATOM_PHY_ID_UNIPHYE ; 
 int /*<<< orphan*/  ATOM_PHY_ID_UNIPHYF ; 
 int /*<<< orphan*/  ATOM_PHY_ID_UNIPHYG ; 
#define  TRANSMITTER_UNIPHY_A 134 
#define  TRANSMITTER_UNIPHY_B 133 
#define  TRANSMITTER_UNIPHY_C 132 
#define  TRANSMITTER_UNIPHY_D 131 
#define  TRANSMITTER_UNIPHY_E 130 
#define  TRANSMITTER_UNIPHY_F 129 
#define  TRANSMITTER_UNIPHY_G 128 

__attribute__((used)) static uint8_t phy_id_to_atom(enum transmitter t)
{
	uint8_t atom_phy_id;

	switch (t) {
	case TRANSMITTER_UNIPHY_A:
		atom_phy_id = ATOM_PHY_ID_UNIPHYA;
		break;
	case TRANSMITTER_UNIPHY_B:
		atom_phy_id = ATOM_PHY_ID_UNIPHYB;
		break;
	case TRANSMITTER_UNIPHY_C:
		atom_phy_id = ATOM_PHY_ID_UNIPHYC;
		break;
	case TRANSMITTER_UNIPHY_D:
		atom_phy_id = ATOM_PHY_ID_UNIPHYD;
		break;
	case TRANSMITTER_UNIPHY_E:
		atom_phy_id = ATOM_PHY_ID_UNIPHYE;
		break;
	case TRANSMITTER_UNIPHY_F:
		atom_phy_id = ATOM_PHY_ID_UNIPHYF;
		break;
	case TRANSMITTER_UNIPHY_G:
		atom_phy_id = ATOM_PHY_ID_UNIPHYG;
		break;
	default:
		atom_phy_id = ATOM_PHY_ID_UNIPHYA;
		break;
	}
	return atom_phy_id;
}