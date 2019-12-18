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
struct ibmvfc_host {scalar_t__ state; scalar_t__ action; int /*<<< orphan*/  init_wait_q; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 scalar_t__ IBMVFC_ACTIVE ; 
 scalar_t__ IBMVFC_HOST_ACTION_NONE ; 
 scalar_t__ IBMVFC_HOST_OFFLINE ; 
 scalar_t__ IBMVFC_LINK_DEAD ; 
 int init_timeout ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ibmvfc_wait_while_resetting(struct ibmvfc_host *vhost)
{
	long timeout = wait_event_timeout(vhost->init_wait_q,
					  ((vhost->state == IBMVFC_ACTIVE ||
					    vhost->state == IBMVFC_HOST_OFFLINE ||
					    vhost->state == IBMVFC_LINK_DEAD) &&
					   vhost->action == IBMVFC_HOST_ACTION_NONE),
					  (init_timeout * HZ));

	return timeout ? 0 : -EIO;
}