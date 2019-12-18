#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ mem_ptr; } ;
typedef  TYPE_1__ ips_ha_t ;

/* Variables and functions */
 scalar_t__ IPS_REG_I2O_HIR ; 
 scalar_t__ IPS_REG_I960_MSG0 ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_flush_and_reset (TYPE_1__*) ; 
 scalar_t__ ips_isintr_morpheus (TYPE_1__*) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static int
ips_isinit_morpheus(ips_ha_t * ha)
{
	uint32_t post;
	uint32_t bits;

	METHOD_TRACE("ips_is_init_morpheus", 1);

	if (ips_isintr_morpheus(ha))
	    ips_flush_and_reset(ha);

	post = readl(ha->mem_ptr + IPS_REG_I960_MSG0);
	bits = readl(ha->mem_ptr + IPS_REG_I2O_HIR);

	if (post == 0)
		return (0);
	else if (bits & 0x3)
		return (0);
	else
		return (1);
}