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
struct stfsm_seq {int dummy; } ;
struct stfsm {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stfsm_load_seq (struct stfsm*,struct stfsm_seq const*) ; 
 struct stfsm_seq stfsm_seq_erase_chip ; 
 int stfsm_wait_busy (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_wait_seq (struct stfsm*) ; 

__attribute__((used)) static int stfsm_erase_chip(struct stfsm *fsm)
{
	const struct stfsm_seq *seq = &stfsm_seq_erase_chip;

	dev_dbg(fsm->dev, "erasing chip\n");

	stfsm_load_seq(fsm, seq);

	stfsm_wait_seq(fsm);

	return stfsm_wait_busy(fsm);
}