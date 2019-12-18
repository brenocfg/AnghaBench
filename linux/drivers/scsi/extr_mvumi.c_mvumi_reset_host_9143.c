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
struct mvumi_hba {int dummy; } ;

/* Variables and functions */
 int mvumi_wait_for_outstanding (struct mvumi_hba*) ; 

__attribute__((used)) static int mvumi_reset_host_9143(struct mvumi_hba *mhba)
{
	return mvumi_wait_for_outstanding(mhba);
}