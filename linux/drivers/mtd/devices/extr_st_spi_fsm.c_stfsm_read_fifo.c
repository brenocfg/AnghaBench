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
typedef  int uint32_t ;
struct stfsm {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SPI_FAST_SEQ_DATA_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  readsl (scalar_t__,int*,int) ; 
 int stfsm_fifo_available (struct stfsm*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void stfsm_read_fifo(struct stfsm *fsm, uint32_t *buf, uint32_t size)
{
	uint32_t remaining = size >> 2;
	uint32_t avail;
	uint32_t words;

	dev_dbg(fsm->dev, "Reading %d bytes from FIFO\n", size);

	BUG_ON((((uintptr_t)buf) & 0x3) || (size & 0x3));

	while (remaining) {
		for (;;) {
			avail = stfsm_fifo_available(fsm);
			if (avail)
				break;
			udelay(1);
		}
		words = min(avail, remaining);
		remaining -= words;

		readsl(fsm->base + SPI_FAST_SEQ_DATA_REG, buf, words);
		buf += words;
	}
}