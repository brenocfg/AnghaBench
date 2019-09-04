#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct mv88e6xxx_port_hwtstamp {int /*<<< orphan*/  state; } ;
struct mv88e6xxx_chip {TYPE_1__* info; struct mv88e6xxx_port_hwtstamp* port_hwtstamp; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptp_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_HWTSTAMP_ENABLED ; 
 int /*<<< orphan*/ * parse_ptp_header (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 *mv88e6xxx_should_tstamp(struct mv88e6xxx_chip *chip, int port,
				   struct sk_buff *skb, unsigned int type)
{
	struct mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	u8 *hdr;

	if (!chip->info->ptp_support)
		return NULL;

	hdr = parse_ptp_header(skb, type);
	if (!hdr)
		return NULL;

	if (!test_bit(MV88E6XXX_HWTSTAMP_ENABLED, &ps->state))
		return NULL;

	return hdr;
}