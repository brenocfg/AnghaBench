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
typedef  int u16 ;
struct proto {int dummy; } ;
struct ppp {struct proto* protos; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t IDX_IPCP ; 
 size_t IDX_IPV6CP ; 
 size_t IDX_LCP ; 
#define  PID_IPCP 130 
#define  PID_IPV6CP 129 
#define  PID_LCP 128 
 struct ppp* get_ppp (struct net_device*) ; 

__attribute__((used)) static inline struct proto* get_proto(struct net_device *dev, u16 pid)
{
	struct ppp *ppp = get_ppp(dev);

	switch (pid) {
	case PID_LCP:
		return &ppp->protos[IDX_LCP];
	case PID_IPCP:
		return &ppp->protos[IDX_IPCP];
	case PID_IPV6CP:
		return &ppp->protos[IDX_IPV6CP];
	default:
		return NULL;
	}
}