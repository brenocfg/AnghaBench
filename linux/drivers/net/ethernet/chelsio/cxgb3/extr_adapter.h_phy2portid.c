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
struct cphy {struct adapter* adapter; } ;
struct port_info {struct cphy phy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct port_info* adap2pinfo (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int phy2portid(struct cphy *phy)
{
	struct adapter *adap = phy->adapter;
	struct port_info *port0 = adap2pinfo(adap, 0);

	return &port0->phy == phy ? 0 : 1;
}