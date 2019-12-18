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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_set_bit_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_10_100_features_array ; 
 int /*<<< orphan*/  phy_10gbit_features ; 
 int /*<<< orphan*/  phy_10gbit_features_array ; 
 int /*<<< orphan*/  phy_10gbit_fec_features ; 
 int /*<<< orphan*/  phy_10gbit_fec_features_array ; 
 int /*<<< orphan*/  phy_10gbit_full_features ; 
 int /*<<< orphan*/  phy_10gbit_full_features_array ; 
 int /*<<< orphan*/  phy_all_ports_features_array ; 
 int /*<<< orphan*/  phy_basic_features ; 
 int /*<<< orphan*/  phy_basic_ports_array ; 
 int /*<<< orphan*/  phy_basic_t1_features ; 
 int /*<<< orphan*/  phy_basic_t1_features_array ; 
 int /*<<< orphan*/  phy_fibre_port_array ; 
 int /*<<< orphan*/  phy_gbit_all_ports_features ; 
 int /*<<< orphan*/  phy_gbit_features ; 
 int /*<<< orphan*/  phy_gbit_features_array ; 
 int /*<<< orphan*/  phy_gbit_fibre_features ; 

__attribute__((used)) static void features_init(void)
{
	/* 10/100 half/full*/
	linkmode_set_bit_array(phy_basic_ports_array,
			       ARRAY_SIZE(phy_basic_ports_array),
			       phy_basic_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_basic_features);

	/* 100 full, TP */
	linkmode_set_bit_array(phy_basic_t1_features_array,
			       ARRAY_SIZE(phy_basic_t1_features_array),
			       phy_basic_t1_features);

	/* 10/100 half/full + 1000 half/full */
	linkmode_set_bit_array(phy_basic_ports_array,
			       ARRAY_SIZE(phy_basic_ports_array),
			       phy_gbit_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_gbit_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_gbit_features);

	/* 10/100 half/full + 1000 half/full + fibre*/
	linkmode_set_bit_array(phy_basic_ports_array,
			       ARRAY_SIZE(phy_basic_ports_array),
			       phy_gbit_fibre_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_gbit_fibre_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_gbit_fibre_features);
	linkmode_set_bit_array(phy_fibre_port_array,
			       ARRAY_SIZE(phy_fibre_port_array),
			       phy_gbit_fibre_features);

	/* 10/100 half/full + 1000 half/full + TP/MII/FIBRE/AUI/BNC/Backplane*/
	linkmode_set_bit_array(phy_all_ports_features_array,
			       ARRAY_SIZE(phy_all_ports_features_array),
			       phy_gbit_all_ports_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_gbit_all_ports_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_gbit_all_ports_features);

	/* 10/100 half/full + 1000 half/full + 10G full*/
	linkmode_set_bit_array(phy_all_ports_features_array,
			       ARRAY_SIZE(phy_all_ports_features_array),
			       phy_10gbit_features);
	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       phy_10gbit_features);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       phy_10gbit_features);
	linkmode_set_bit_array(phy_10gbit_features_array,
			       ARRAY_SIZE(phy_10gbit_features_array),
			       phy_10gbit_features);

	/* 10/100/1000/10G full */
	linkmode_set_bit_array(phy_all_ports_features_array,
			       ARRAY_SIZE(phy_all_ports_features_array),
			       phy_10gbit_full_features);
	linkmode_set_bit_array(phy_10gbit_full_features_array,
			       ARRAY_SIZE(phy_10gbit_full_features_array),
			       phy_10gbit_full_features);
	/* 10G FEC only */
	linkmode_set_bit_array(phy_10gbit_fec_features_array,
			       ARRAY_SIZE(phy_10gbit_fec_features_array),
			       phy_10gbit_fec_features);
}