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
 int /*<<< orphan*/  writesl (scalar_t__,int const*,int) ; 

__attribute__((used)) static int stfsm_write_fifo(struct stfsm *fsm, const uint32_t *buf,
			    uint32_t size)
{
	uint32_t words = size >> 2;

	dev_dbg(fsm->dev, "writing %d bytes to FIFO\n", size);

	BUG_ON((((uintptr_t)buf) & 0x3) || (size & 0x3));

	writesl(fsm->base + SPI_FAST_SEQ_DATA_REG, buf, words);

	return size;
}