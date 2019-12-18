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
struct brcms_pub {scalar_t__ wlc; } ;
struct brcms_info {int dummy; } ;
struct brcms_c_info {TYPE_1__* modulecb; } ;
struct TYPE_2__ {struct brcms_info* hdl; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BRCMS_MAXMODULES ; 
 int ENODATA ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int brcms_c_module_unregister(struct brcms_pub *pub, const char *name,
			      struct brcms_info *hdl)
{
	struct brcms_c_info *wlc = (struct brcms_c_info *) pub->wlc;
	int i;

	if (wlc == NULL)
		return -ENODATA;

	for (i = 0; i < BRCMS_MAXMODULES; i++) {
		if (!strcmp(wlc->modulecb[i].name, name) &&
		    (wlc->modulecb[i].hdl == hdl)) {
			memset(&wlc->modulecb[i], 0, sizeof(wlc->modulecb[i]));
			return 0;
		}
	}

	/* table not found! */
	return -ENODATA;
}