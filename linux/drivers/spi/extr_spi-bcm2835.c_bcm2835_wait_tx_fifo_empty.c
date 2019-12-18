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
struct bcm2835_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_SPI_CS ; 
 int BCM2835_SPI_CS_DONE ; 
 int bcm2835_rd (struct bcm2835_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static inline void bcm2835_wait_tx_fifo_empty(struct bcm2835_spi *bs)
{
	while (!(bcm2835_rd(bs, BCM2835_SPI_CS) & BCM2835_SPI_CS_DONE))
		cpu_relax();
}