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
typedef  int /*<<< orphan*/  u32 ;
struct net {int dummy; } ;
struct hwsim_net {int /*<<< orphan*/  wmediumd; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsim_net_id ; 
 struct hwsim_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 hwsim_net_get_wmediumd(struct net *net)
{
	struct hwsim_net *hwsim_net = net_generic(net, hwsim_net_id);

	return hwsim_net->wmediumd;
}