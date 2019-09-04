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
struct adv7511 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_REG_PACKET_ENABLE0 ; 
 int /*<<< orphan*/  ADV7511_REG_PACKET_ENABLE1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int adv7511_packet_enable(struct adv7511 *adv7511, unsigned int packet)
{
	if (packet & 0xff)
		regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE0,
				   packet, 0xff);

	if (packet & 0xff00) {
		packet >>= 8;
		regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				   packet, 0xff);
	}

	return 0;
}