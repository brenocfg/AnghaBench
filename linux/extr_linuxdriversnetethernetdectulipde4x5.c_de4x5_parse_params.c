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
struct net_device {char* name; } ;
struct TYPE_2__ {int fdx; void* autosense; } ;
struct de4x5_private {TYPE_1__ params; } ;

/* Variables and functions */
 void* AUI ; 
 void* AUTO ; 
 void* BNC ; 
 void* TP ; 
 void* TP_NW ; 
 void* _100Mb ; 
 void* _10Mb ; 
 char* args ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
de4x5_parse_params(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    char *p, *q, t;

    lp->params.fdx = false;
    lp->params.autosense = AUTO;

    if (args == NULL) return;

    if ((p = strstr(args, dev->name))) {
	if (!(q = strstr(p+strlen(dev->name), "eth"))) q = p + strlen(p);
	t = *q;
	*q = '\0';

	if (strstr(p, "fdx") || strstr(p, "FDX")) lp->params.fdx = true;

	if (strstr(p, "autosense") || strstr(p, "AUTOSENSE")) {
	    if (strstr(p, "TP_NW")) {
		lp->params.autosense = TP_NW;
	    } else if (strstr(p, "TP")) {
		lp->params.autosense = TP;
	    } else if (strstr(p, "BNC_AUI")) {
		lp->params.autosense = BNC;
	    } else if (strstr(p, "BNC")) {
		lp->params.autosense = BNC;
	    } else if (strstr(p, "AUI")) {
		lp->params.autosense = AUI;
	    } else if (strstr(p, "10Mb")) {
		lp->params.autosense = _10Mb;
	    } else if (strstr(p, "100Mb")) {
		lp->params.autosense = _100Mb;
	    } else if (strstr(p, "AUTO")) {
		lp->params.autosense = AUTO;
	    }
	}
	*q = t;
    }
}