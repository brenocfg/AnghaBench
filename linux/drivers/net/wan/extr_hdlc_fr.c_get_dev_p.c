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
struct pvc_device {struct net_device* main; struct net_device* ether; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ARPHRD_ETHER ; 

__attribute__((used)) static inline struct net_device **get_dev_p(struct pvc_device *pvc,
					    int type)
{
	if (type == ARPHRD_ETHER)
		return &pvc->ether;
	else
		return &pvc->main;
}