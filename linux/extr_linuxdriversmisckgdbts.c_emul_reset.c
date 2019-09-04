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
struct TYPE_2__ {int idx; } ;

/* Variables and functions */
 scalar_t__ restart_from_top_after_write ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 TYPE_1__ ts ; 

__attribute__((used)) static int emul_reset(char *put_str, char *arg)
{
	if (strncmp(put_str, "$OK", 3))
		return 1;
	if (restart_from_top_after_write) {
		restart_from_top_after_write = 0;
		ts.idx = -1;
	}
	return 0;
}