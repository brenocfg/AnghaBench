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
struct mmc_spi_host {int dummy; } ;

/* Variables and functions */
 int mmc_spi_skip (struct mmc_spi_host*,unsigned long,int,int) ; 

__attribute__((used)) static int mmc_spi_readtoken(struct mmc_spi_host *host, unsigned long timeout)
{
	return mmc_spi_skip(host, timeout, 1, 0xff);
}