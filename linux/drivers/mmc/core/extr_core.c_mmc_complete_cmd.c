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
struct mmc_request {int /*<<< orphan*/  cmd_completion; scalar_t__ cap_cmd_during_tfr; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mmc_complete_cmd(struct mmc_request *mrq)
{
	if (mrq->cap_cmd_during_tfr && !completion_done(&mrq->cmd_completion))
		complete_all(&mrq->cmd_completion);
}