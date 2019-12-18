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
typedef  int /*<<< orphan*/  u8 ;
struct security_priv {TYPE_1__* PMKIDList; } ;
struct adapter {struct security_priv securitypriv; } ;
struct TYPE_2__ {int /*<<< orphan*/  Bssid; scalar_t__ bUsed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int NUM_PMKID_CACHE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SecIsInPMKIDList(struct adapter *Adapter, u8 *bssid)
{
	struct security_priv *psecuritypriv = &Adapter->securitypriv;
	int i = 0;

	do {
		if ((psecuritypriv->PMKIDList[i].bUsed) &&
				(!memcmp(psecuritypriv->PMKIDList[i].Bssid, bssid, ETH_ALEN))) {
			break;
		} else {
			i++;
			/* continue; */
		}

	} while (i < NUM_PMKID_CACHE);

	if (i == NUM_PMKID_CACHE) {
		i = -1;/*  Could not find. */
	} else {
		/*  There is one Pre-Authentication Key for the specific BSSID. */
	}

	return i;

}