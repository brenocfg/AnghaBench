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
struct atmel_mci {unsigned int bus_hz; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 

__attribute__((used)) static inline unsigned int atmci_ns_to_clocks(struct atmel_mci *host,
					unsigned int ns)
{
	/*
	 * It is easier here to use us instead of ns for the timeout,
	 * it prevents from overflows during calculation.
	 */
	unsigned int us = DIV_ROUND_UP(ns, 1000);

	/* Maximum clock frequency is host->bus_hz/2 */
	return us * (DIV_ROUND_UP(host->bus_hz, 2000000));
}