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
struct sigscratch {int dummy; } ;
struct ksignal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int setup_frame (struct ksignal*,int /*<<< orphan*/ ,struct sigscratch*) ; 
 int /*<<< orphan*/  sigmask_to_save () ; 
 int /*<<< orphan*/  signal_setup_done (int,struct ksignal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
handle_signal (struct ksignal *ksig, struct sigscratch *scr)
{
	int ret = setup_frame(ksig, sigmask_to_save(), scr);

	if (!ret)
		signal_setup_done(ret, ksig, test_thread_flag(TIF_SINGLESTEP));

	return ret;
}