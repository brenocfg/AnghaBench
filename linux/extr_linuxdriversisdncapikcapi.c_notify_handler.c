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
typedef  long u32 ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CAPICTR_DOWN 129 
#define  CAPICTR_UP 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  notify_down (long) ; 
 int /*<<< orphan*/  notify_up (long) ; 

__attribute__((used)) static int
notify_handler(struct notifier_block *nb, unsigned long val, void *v)
{
	u32 contr = (long)v;

	switch (val) {
	case CAPICTR_UP:
		notify_up(contr);
		break;
	case CAPICTR_DOWN:
		notify_down(contr);
		break;
	}
	return NOTIFY_OK;
}