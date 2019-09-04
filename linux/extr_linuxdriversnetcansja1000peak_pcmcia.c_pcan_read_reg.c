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
typedef  int /*<<< orphan*/  u8 ;
struct pcan_pccard {scalar_t__ ioport_addr; } ;

/* Variables and functions */
 scalar_t__ PCC_COMN_OFF ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 

__attribute__((used)) static u8 pcan_read_reg(struct pcan_pccard *card, int port)
{
	return ioread8(card->ioport_addr + PCC_COMN_OFF + port);
}