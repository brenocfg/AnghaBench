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
struct work_struct {int dummy; } ;
struct octeon_mbox {int dummy; } ;
struct cavium_wk {scalar_t__ ctxptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  octeon_mbox_process_message (struct octeon_mbox*) ; 

__attribute__((used)) static void cn23xx_vf_mbox_thread(struct work_struct *work)
{
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct octeon_mbox *mbox = (struct octeon_mbox *)wk->ctxptr;

	octeon_mbox_process_message(mbox);
}