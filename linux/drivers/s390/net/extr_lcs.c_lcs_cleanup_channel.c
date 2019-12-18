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
struct lcs_channel {int /*<<< orphan*/  irq_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lcs_free_channel (struct lcs_channel*) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lcs_cleanup_channel(struct lcs_channel *channel)
{
	LCS_DBF_TEXT(3, setup, "cleanch");
	/* Kill write channel tasklets. */
	tasklet_kill(&channel->irq_tasklet);
	/* Free channel buffers. */
	lcs_free_channel(channel);
}