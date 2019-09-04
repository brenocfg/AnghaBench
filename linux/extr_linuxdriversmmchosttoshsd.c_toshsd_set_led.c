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
struct toshsd_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ SDIO_BASE ; 
 scalar_t__ SDIO_LEDCTRL ; 
 int /*<<< orphan*/  iowrite16 (unsigned char,scalar_t__) ; 

__attribute__((used)) static void toshsd_set_led(struct toshsd_host *host, unsigned char state)
{
	iowrite16(state, host->ioaddr + SDIO_BASE + SDIO_LEDCTRL);
}