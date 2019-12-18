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
struct ap_queue {int dummy; } ;
typedef  enum ap_wait { ____Placeholder_ap_wait } ap_wait ;

/* Variables and functions */
 int /*<<< orphan*/  ap_sm_read (struct ap_queue*) ; 
 int /*<<< orphan*/  ap_sm_write (struct ap_queue*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ap_wait ap_sm_read_write(struct ap_queue *aq)
{
	return min(ap_sm_read(aq), ap_sm_write(aq));
}