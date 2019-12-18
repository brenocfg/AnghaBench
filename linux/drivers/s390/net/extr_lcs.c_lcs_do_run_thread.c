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
struct lcs_card {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 int __lcs_do_run_thread (struct lcs_card*,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lcs_do_run_thread(struct lcs_card *card, unsigned long thread)
{
        int rc = 0;
        wait_event(card->wait_q,
                   (rc = __lcs_do_run_thread(card, thread)) >= 0);
        return rc;
}