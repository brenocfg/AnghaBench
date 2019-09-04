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
struct elan_tp_data {int dummy; } ;

/* Variables and functions */
 int ETP_RETRY_COUNT ; 
 int __elan_initialize (struct elan_tp_data*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int elan_initialize(struct elan_tp_data *data)
{
	int repeat = ETP_RETRY_COUNT;
	int error;

	do {
		error = __elan_initialize(data);
		if (!error)
			return 0;

		msleep(30);
	} while (--repeat > 0);

	return error;
}