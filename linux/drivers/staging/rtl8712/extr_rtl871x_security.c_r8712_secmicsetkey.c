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
typedef  int /*<<< orphan*/  u8 ;
struct mic_data {void* K1; void* K0; } ;

/* Variables and functions */
 int /*<<< orphan*/  secmicclear (struct mic_data*) ; 
 void* secmicgetuint32 (int /*<<< orphan*/ *) ; 

void r8712_secmicsetkey(struct mic_data *pmicdata, u8 *key)
{
	/* Set the key */
	pmicdata->K0 = secmicgetuint32(key);
	pmicdata->K1 = secmicgetuint32(key + 4);
	/* and reset the message */
	secmicclear(pmicdata);
}