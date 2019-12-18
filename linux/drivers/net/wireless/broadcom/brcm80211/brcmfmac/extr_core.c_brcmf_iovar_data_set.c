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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_bus {TYPE_1__* drvr; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {struct brcmf_if** iflist; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_fil_iovar_data_set (struct brcmf_if*,char*,void*,int /*<<< orphan*/ ) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 

s32 brcmf_iovar_data_set(struct device *dev, char *name, void *data, u32 len)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_if *ifp = bus_if->drvr->iflist[0];

	return brcmf_fil_iovar_data_set(ifp, name, data, len);
}