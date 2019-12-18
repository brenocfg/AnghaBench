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
struct device {int dummy; } ;
struct brcmf_pub {scalar_t__* iflist; } ;
struct brcmf_bus {struct brcmf_pub* drvr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_TERMINATED ; 
 int /*<<< orphan*/  brcmf_fil_cmd_int_set (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 

void brcmf_dev_reset(struct device *dev)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_pub *drvr = bus_if->drvr;

	if (drvr == NULL)
		return;

	if (drvr->iflist[0])
		brcmf_fil_cmd_int_set(drvr->iflist[0], BRCMF_C_TERMINATED, 1);
}