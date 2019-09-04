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
struct mbox_chan {int /*<<< orphan*/  con_priv; } ;

/* Variables and functions */
 int flexrm_process_completions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool flexrm_peek_data(struct mbox_chan *chan)
{
	int cnt = flexrm_process_completions(chan->con_priv);

	return (cnt > 0) ? true : false;
}