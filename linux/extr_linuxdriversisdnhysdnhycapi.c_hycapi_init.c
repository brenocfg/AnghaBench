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
typedef  int /*<<< orphan*/  hycapi_appl ;

/* Variables and functions */
 int CAPI_MAXAPPL ; 
 int /*<<< orphan*/ * hycapi_applications ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int hycapi_init(void)
{
	int i;
	for (i = 0; i < CAPI_MAXAPPL; i++) {
		memset(&(hycapi_applications[i]), 0, sizeof(hycapi_appl));
	}
	return (0);
}