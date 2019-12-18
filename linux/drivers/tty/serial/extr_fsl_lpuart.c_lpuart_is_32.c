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
struct TYPE_2__ {scalar_t__ iotype; } ;
struct lpuart_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UPIO_MEM32 ; 
 scalar_t__ UPIO_MEM32BE ; 

__attribute__((used)) static bool lpuart_is_32(struct lpuart_port *sport)
{
	return sport->port.iotype == UPIO_MEM32 ||
	       sport->port.iotype ==  UPIO_MEM32BE;
}