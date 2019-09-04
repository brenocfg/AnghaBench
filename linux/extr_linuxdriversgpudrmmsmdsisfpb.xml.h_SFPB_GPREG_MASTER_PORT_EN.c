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
typedef  int uint32_t ;
typedef  enum sfpb_ahb_arb_master_port_en { ____Placeholder_sfpb_ahb_arb_master_port_en } sfpb_ahb_arb_master_port_en ;

/* Variables and functions */
 int SFPB_GPREG_MASTER_PORT_EN__MASK ; 
 int SFPB_GPREG_MASTER_PORT_EN__SHIFT ; 

__attribute__((used)) static inline uint32_t SFPB_GPREG_MASTER_PORT_EN(enum sfpb_ahb_arb_master_port_en val)
{
	return ((val) << SFPB_GPREG_MASTER_PORT_EN__SHIFT) & SFPB_GPREG_MASTER_PORT_EN__MASK;
}