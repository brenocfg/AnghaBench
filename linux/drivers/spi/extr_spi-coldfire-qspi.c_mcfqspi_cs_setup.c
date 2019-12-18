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
struct mcfqspi {TYPE_1__* cs_control; } ;
struct TYPE_2__ {int (* setup ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int mcfqspi_cs_setup(struct mcfqspi *mcfqspi)
{
	return (mcfqspi->cs_control->setup) ?
		mcfqspi->cs_control->setup(mcfqspi->cs_control) : 0;
}