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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct stfsm_seq {int dummy; } ;
struct stfsm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stfsm_load_seq (struct stfsm*,struct stfsm_seq const*) ; 
 int /*<<< orphan*/  stfsm_read_fifo (struct stfsm*,int /*<<< orphan*/ *,int) ; 
 struct stfsm_seq stfsm_seq_read_jedec ; 
 int /*<<< orphan*/  stfsm_wait_seq (struct stfsm*) ; 

__attribute__((used)) static void stfsm_read_jedec(struct stfsm *fsm, uint8_t *jedec)
{
	const struct stfsm_seq *seq = &stfsm_seq_read_jedec;
	uint32_t tmp[2];

	stfsm_load_seq(fsm, seq);

	stfsm_read_fifo(fsm, tmp, 8);

	memcpy(jedec, tmp, 5);

	stfsm_wait_seq(fsm);
}