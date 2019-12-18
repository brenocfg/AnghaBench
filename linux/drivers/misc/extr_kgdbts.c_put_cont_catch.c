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
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sstep_thread_id ; 
 TYPE_1__ ts ; 
 int /*<<< orphan*/  v2printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int put_cont_catch(char *put_str, char *arg)
{
	/* This is at the end of the test and we catch any and all input */
	v2printk("kgdbts: cleanup task: %lx\n", sstep_thread_id);
	ts.idx--;
	return 0;
}