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
struct TYPE_2__ {int /*<<< orphan*/  tx_comp; } ;
struct bnad {TYPE_1__ bnad_completions; } ;
struct bna_tx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_cb_tx_disabled(void *arg, struct bna_tx *tx)
{
	struct bnad *bnad = (struct bnad *)arg;

	complete(&bnad->bnad_completions.tx_comp);
}