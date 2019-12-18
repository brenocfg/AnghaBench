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

/* Variables and functions */
 int /*<<< orphan*/  deactfsm ; 
 int /*<<< orphan*/  mISDN_FsmFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teifsmn ; 
 int /*<<< orphan*/  teifsmu ; 

void TEIFree(void)
{
	mISDN_FsmFree(&teifsmu);
	mISDN_FsmFree(&teifsmn);
	mISDN_FsmFree(&deactfsm);
}