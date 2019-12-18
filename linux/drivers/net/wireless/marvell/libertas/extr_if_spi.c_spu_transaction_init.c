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
struct if_spi_card {scalar_t__ prev_xfer_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void spu_transaction_init(struct if_spi_card *card)
{
	if (!time_after(jiffies, card->prev_xfer_time + 1)) {
		/* Unfortunately, the SPU requires a delay between successive
		 * transactions. If our last transaction was more than a jiffy
		 * ago, we have obviously already delayed enough.
		 * If not, we have to busy-wait to be on the safe side. */
		ndelay(400);
	}
}