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
typedef  scalar_t__ u16 ;
struct mgsl_struct {scalar_t__ bus_type; int /*<<< orphan*/  io_base; scalar_t__ mbre_bit; } ;

/* Variables and functions */
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usc_DmaCmd( struct mgsl_struct *info, u16 Cmd )
{
	/* write command mask to DCAR */
	outw( Cmd + info->mbre_bit, info->io_base );

	/* Read to flush write to DCAR */
	if ( info->bus_type == MGSL_BUS_TYPE_PCI )
		inw( info->io_base );

}