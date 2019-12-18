#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct stfsm {int /*<<< orphan*/  dev; int /*<<< orphan*/  stfsm_seq_write; int /*<<< orphan*/  stfsm_seq_read; TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_read_configs ; 
 int /*<<< orphan*/  default_write_configs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stfsm_prepare_erasesec_seq (struct stfsm*,int /*<<< orphan*/ *) ; 
 int stfsm_search_prepare_rw_seq (struct stfsm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stfsm_seq_erase_sector ; 

__attribute__((used)) static int stfsm_prepare_rwe_seqs_default(struct stfsm *fsm)
{
	uint32_t flags = fsm->info->flags;
	int ret;

	/* Configure 'READ' sequence */
	ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_read,
					  default_read_configs);
	if (ret) {
		dev_err(fsm->dev,
			"failed to prep READ sequence with flags [0x%08x]\n",
			flags);
		return ret;
	}

	/* Configure 'WRITE' sequence */
	ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_write,
					  default_write_configs);
	if (ret) {
		dev_err(fsm->dev,
			"failed to prep WRITE sequence with flags [0x%08x]\n",
			flags);
		return ret;
	}

	/* Configure 'ERASE_SECTOR' sequence */
	stfsm_prepare_erasesec_seq(fsm, &stfsm_seq_erase_sector);

	return 0;
}