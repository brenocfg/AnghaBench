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
struct TYPE_2__ {int /*<<< orphan*/  port; scalar_t__ cmd; scalar_t__ duplex; scalar_t__ speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  diff1 ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (struct ethtool_link_ksettings*,struct ethtool_link_ksettings*,int) ; 

__attribute__((used)) static bool
netvsc_validate_ethtool_ss_cmd(const struct ethtool_link_ksettings *cmd)
{
	struct ethtool_link_ksettings diff1 = *cmd;
	struct ethtool_link_ksettings diff2 = {};

	diff1.base.speed = 0;
	diff1.base.duplex = 0;
	/* advertising and cmd are usually set */
	ethtool_link_ksettings_zero_link_mode(&diff1, advertising);
	diff1.base.cmd = 0;
	/* We set port to PORT_OTHER */
	diff2.base.port = PORT_OTHER;

	return !memcmp(&diff1, &diff2, sizeof(diff1));
}