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
struct de4x5_private {char srom; } ;

/* Variables and functions */
 int ACCTON ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int SMC ; 
 int /*<<< orphan*/ * enet_det ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
de4x5_bad_srom(struct de4x5_private *lp)
{
    int i, status = 0;

    for (i = 0; i < ARRAY_SIZE(enet_det); i++) {
	if (!memcmp(&lp->srom, &enet_det[i], 3) &&
	    !memcmp((char *)&lp->srom+0x10, &enet_det[i], 3)) {
	    if (i == 0) {
		status = SMC;
	    } else if (i == 1) {
		status = ACCTON;
	    }
	    break;
	}
    }

    return status;
}