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
typedef  int u32 ;
struct net_device {int* dev_addr; } ;
struct ks8695_priv {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8695_MAH ; 
 int /*<<< orphan*/  KS8695_MAL ; 
 int /*<<< orphan*/  ks8695_writereg (struct ks8695_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ks8695_update_mac(struct ks8695_priv *ksp)
{
	/* Update the HW with the MAC from the net_device */
	struct net_device *ndev = ksp->ndev;
	u32 machigh, maclow;

	maclow	= ((ndev->dev_addr[2] << 24) | (ndev->dev_addr[3] << 16) |
		   (ndev->dev_addr[4] <<  8) | (ndev->dev_addr[5] <<  0));
	machigh = ((ndev->dev_addr[0] <<  8) | (ndev->dev_addr[1] <<  0));

	ks8695_writereg(ksp, KS8695_MAL, maclow);
	ks8695_writereg(ksp, KS8695_MAH, machigh);

}