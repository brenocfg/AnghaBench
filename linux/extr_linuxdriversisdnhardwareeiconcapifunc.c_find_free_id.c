#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int MAX_DESCRIPTORS ; 
 TYPE_1__* adapter ; 

__attribute__((used)) static int find_free_id(void)
{
	int num = 0;
	DIVA_CAPI_ADAPTER *a;

	while (num < MAX_DESCRIPTORS) {
		a = &adapter[num];
		if (!a->Id)
			break;
		num++;
	}
	return (num + 1);
}