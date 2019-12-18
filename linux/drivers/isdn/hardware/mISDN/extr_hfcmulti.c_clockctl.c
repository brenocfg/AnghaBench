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
struct hfc_multi {int iclock_on; } ;

/* Variables and functions */

__attribute__((used)) static int
clockctl(void *priv, int enable)
{
	struct hfc_multi *hc = priv;

	hc->iclock_on = enable;
	return 0;
}