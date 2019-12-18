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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_tracesink_datadrain (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  routelock ; 

__attribute__((used)) static void n_tracerouter_receivebuf(struct tty_struct *tty,
					const unsigned char *cp,
					char *fp, int count)
{
	mutex_lock(&routelock);
	n_tracesink_datadrain((u8 *) cp, count);
	mutex_unlock(&routelock);
}