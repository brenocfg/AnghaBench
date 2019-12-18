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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  NETEVENT_NEIGH_UPDATE 129 
#define  NETEVENT_REDIRECT 128 
 int /*<<< orphan*/  check_neigh_update (void*) ; 

__attribute__((used)) static int netevent_cb(struct notifier_block *nb, unsigned long event,
		       void *data)
{
	switch (event) {
	case NETEVENT_NEIGH_UPDATE:
		check_neigh_update(data);
		break;
	case NETEVENT_REDIRECT:
	default:
		break;
	}
	return 0;
}