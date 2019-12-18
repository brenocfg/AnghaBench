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
struct stfsm_seq {int dummy; } ;
struct stfsm {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPI_FAST_SEQ_DATA_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int stfsm_fifo_available (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_load_seq (struct stfsm*,struct stfsm_seq const*) ; 
 struct stfsm_seq stfsm_seq_load_fifo_byte ; 
 int /*<<< orphan*/  stfsm_wait_seq (struct stfsm*) ; 

__attribute__((used)) static void stfsm_clear_fifo(struct stfsm *fsm)
{
	const struct stfsm_seq *seq = &stfsm_seq_load_fifo_byte;
	uint32_t words, i;

	/* 1. Clear any 32-bit words */
	words = stfsm_fifo_available(fsm);
	if (words) {
		for (i = 0; i < words; i++)
			readl(fsm->base + SPI_FAST_SEQ_DATA_REG);
		dev_dbg(fsm->dev, "cleared %d words from FIFO\n", words);
	}

	/*
	 * 2. Clear any remaining bytes
	 *    - Load the FIFO, one byte at a time, until a complete 32-bit word
	 *      is available.
	 */
	for (i = 0, words = 0; i < 4 && !words; i++) {
		stfsm_load_seq(fsm, seq);
		stfsm_wait_seq(fsm);
		words = stfsm_fifo_available(fsm);
	}

	/*    - A single word must be available now */
	if (words != 1) {
		dev_err(fsm->dev, "failed to clear bytes from the data FIFO\n");
		return;
	}

	/*    - Read the 32-bit word */
	readl(fsm->base + SPI_FAST_SEQ_DATA_REG);

	dev_dbg(fsm->dev, "cleared %d byte(s) from the data FIFO\n", 4 - i);
}