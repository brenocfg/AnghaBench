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
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct obj_mlme {int id; int /*<<< orphan*/  address; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  DOT11_OID_DISASSOCIATE ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct obj_mlme*) ; 
 struct obj_mlme* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mgt_set_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct obj_mlme*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_kick_mac(struct net_device *ndev, struct iw_request_info *info,
		 struct sockaddr *awrq, char *extra)
{
	struct obj_mlme *mlme;
	struct sockaddr *addr = (struct sockaddr *) extra;
	int rvalue;

	if (addr->sa_family != ARPHRD_ETHER)
		return -EOPNOTSUPP;

	mlme = kmalloc(sizeof (struct obj_mlme), GFP_KERNEL);
	if (mlme == NULL)
		return -ENOMEM;

	/* Tell the card to only kick the corresponding bastard */
	memcpy(mlme->address, addr->sa_data, ETH_ALEN);
	mlme->id = -1;
	rvalue =
	    mgt_set_request(netdev_priv(ndev), DOT11_OID_DISASSOCIATE, 0, mlme);

	kfree(mlme);

	return rvalue;
}