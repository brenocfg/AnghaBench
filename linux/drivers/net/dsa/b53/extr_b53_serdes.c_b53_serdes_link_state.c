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
typedef  int u16 ;
struct phylink_link_state {int an_complete; int link; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ B53_INVALID_LANE ; 
 int /*<<< orphan*/  B53_SERDES_DIGITAL_STATUS ; 
 int /*<<< orphan*/  B53_SERDES_MII_REG (int /*<<< orphan*/ ) ; 
 int BMSR_ANEGCOMPLETE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int DUPLEX_STATUS ; 
 int LINK_STATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MLO_PAUSE_RX ; 
 int /*<<< orphan*/  MLO_PAUSE_TX ; 
 int PAUSE_RESOLUTION_RX_SIDE ; 
 int PAUSE_RESOLUTION_TX_SIDE ; 
 int /*<<< orphan*/  SERDES_DIGITAL_BLK ; 
 int /*<<< orphan*/  SERDES_MII_BLK ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
#define  SPEED_STATUS_10 131 
#define  SPEED_STATUS_100 130 
#define  SPEED_STATUS_1000 129 
#define  SPEED_STATUS_2500 128 
 int SPEED_STATUS_MASK ; 
 int SPEED_STATUS_SHIFT ; 
 scalar_t__ b53_serdes_map_lane (struct b53_device*,int) ; 
 int b53_serdes_read (struct b53_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int b53_serdes_link_state(struct b53_device *dev, int port,
			  struct phylink_link_state *state)
{
	u8 lane = b53_serdes_map_lane(dev, port);
	u16 dig, bmsr;

	if (lane == B53_INVALID_LANE)
		return 1;

	dig = b53_serdes_read(dev, lane, B53_SERDES_DIGITAL_STATUS,
			      SERDES_DIGITAL_BLK);
	bmsr = b53_serdes_read(dev, lane, B53_SERDES_MII_REG(MII_BMSR),
			       SERDES_MII_BLK);

	switch ((dig >> SPEED_STATUS_SHIFT) & SPEED_STATUS_MASK) {
	case SPEED_STATUS_10:
		state->speed = SPEED_10;
		break;
	case SPEED_STATUS_100:
		state->speed = SPEED_100;
		break;
	case SPEED_STATUS_1000:
		state->speed = SPEED_1000;
		break;
	default:
	case SPEED_STATUS_2500:
		state->speed = SPEED_2500;
		break;
	}

	state->duplex = dig & DUPLEX_STATUS ? DUPLEX_FULL : DUPLEX_HALF;
	state->an_complete = !!(bmsr & BMSR_ANEGCOMPLETE);
	state->link = !!(dig & LINK_STATUS);
	if (dig & PAUSE_RESOLUTION_RX_SIDE)
		state->pause |= MLO_PAUSE_RX;
	if (dig & PAUSE_RESOLUTION_TX_SIDE)
		state->pause |= MLO_PAUSE_TX;

	return 0;
}