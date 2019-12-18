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
struct obj_mlme {scalar_t__ id; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_OID_DISASSOCIATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct obj_mlme*) ; 
 struct obj_mlme* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mgt_set_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct obj_mlme*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_kick_all(struct net_device *ndev, struct iw_request_info *info,
		 struct iw_point *dwrq, char *extra)
{
	struct obj_mlme *mlme;
	int rvalue;

	mlme = kmalloc(sizeof (struct obj_mlme), GFP_KERNEL);
	if (mlme == NULL)
		return -ENOMEM;

	/* Tell the card to kick every client */
	mlme->id = 0;
	rvalue =
	    mgt_set_request(netdev_priv(ndev), DOT11_OID_DISASSOCIATE, 0, mlme);
	kfree(mlme);

	return rvalue;
}