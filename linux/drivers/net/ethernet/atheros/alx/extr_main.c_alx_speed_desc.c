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
struct alx_hw {int /*<<< orphan*/  duplex; int /*<<< orphan*/  link_speed; } ;

/* Variables and functions */
#define  ADVERTISED_1000baseT_Full 132 
#define  ADVERTISED_100baseT_Full 131 
#define  ADVERTISED_100baseT_Half 130 
#define  ADVERTISED_10baseT_Full 129 
#define  ADVERTISED_10baseT_Half 128 
 int alx_speed_to_ethadv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *alx_speed_desc(struct alx_hw *hw)
{
	switch (alx_speed_to_ethadv(hw->link_speed, hw->duplex)) {
	case ADVERTISED_1000baseT_Full:
		return "1 Gbps Full";
	case ADVERTISED_100baseT_Full:
		return "100 Mbps Full";
	case ADVERTISED_100baseT_Half:
		return "100 Mbps Half";
	case ADVERTISED_10baseT_Full:
		return "10 Mbps Full";
	case ADVERTISED_10baseT_Half:
		return "10 Mbps Half";
	default:
		return "Unknown speed";
	}
}