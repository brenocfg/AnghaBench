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
struct port_info {int dummy; } ;
struct adapter {int /*<<< orphan*/ * port; } ;

/* Variables and functions */
 struct port_info* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct port_info *adap2pinfo(struct adapter *adap, int idx)
{
	return netdev_priv(adap->port[idx]);
}