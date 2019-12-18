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
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int mmc_io_rw_direct_host (int /*<<< orphan*/ ,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mmc_io_rw_direct(struct mmc_card *card, int write, unsigned fn,
	unsigned addr, u8 in, u8 *out)
{
	return mmc_io_rw_direct_host(card->host, write, fn, addr, in, out);
}