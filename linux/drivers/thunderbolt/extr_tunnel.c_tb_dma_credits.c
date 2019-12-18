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
typedef  int u32 ;
struct TYPE_2__ {int nfc_credits; } ;
struct tb_port {TYPE_1__ config; } ;

/* Variables and functions */
 int TB_PORT_MAX_CREDITS_MASK ; 
 int TB_PORT_MAX_CREDITS_SHIFT ; 
 int min (int,unsigned int) ; 

__attribute__((used)) static u32 tb_dma_credits(struct tb_port *nhi)
{
	u32 max_credits;

	max_credits = (nhi->config.nfc_credits & TB_PORT_MAX_CREDITS_MASK) >>
		TB_PORT_MAX_CREDITS_SHIFT;
	return min(max_credits, 13U);
}