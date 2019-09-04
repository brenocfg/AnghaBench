#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct suni_priv {int dummy; } ;
struct atm_dev {int /*<<< orphan*/ * phy; int /*<<< orphan*/  phy_data; } ;
struct TYPE_2__ {unsigned char type; struct atm_dev* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned char GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MRI ; 
 int /*<<< orphan*/  MT ; 
 TYPE_1__* PRIV (struct atm_dev*) ; 
 int /*<<< orphan*/  PUT (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CHANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char SUNI_IDLE_PATTERN ; 
 unsigned char SUNI_MRI_RESET ; 
 unsigned char SUNI_MRI_TYPE ; 
 unsigned char SUNI_MRI_TYPE_SHIFT ; 
 unsigned char SUNI_MT_DS27_53 ; 
 int /*<<< orphan*/  SUNI_TACP_IUCHP_CLP ; 
 int /*<<< orphan*/  TACP_IUCHP ; 
 int /*<<< orphan*/  TACP_IUCPOP ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sonet (struct atm_dev*) ; 
 int /*<<< orphan*/  suni_ops ; 

int suni_init(struct atm_dev *dev)
{
	unsigned char mri;

	if (!(dev->phy_data = kmalloc(sizeof(struct suni_priv),GFP_KERNEL)))
		return -ENOMEM;
	PRIV(dev)->dev = dev;

	mri = GET(MRI); /* reset SUNI */
	PRIV(dev)->type = (mri & SUNI_MRI_TYPE) >> SUNI_MRI_TYPE_SHIFT;
	PUT(mri | SUNI_MRI_RESET,MRI);
	PUT(mri,MRI);
	PUT((GET(MT) & SUNI_MT_DS27_53),MT); /* disable all tests */
        set_sonet(dev);
	REG_CHANGE(SUNI_TACP_IUCHP_CLP,0,SUNI_TACP_IUCHP_CLP,
	    TACP_IUCHP); /* idle cells */
	PUT(SUNI_IDLE_PATTERN,TACP_IUCPOP);
	dev->phy = &suni_ops;

	return 0;
}