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
struct ds1307 {int type; int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
#define  m41t0 130 
#define  m41t00 129 
#define  m41t11 128 
 int rtc_add_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_freq_test_attr_group ; 

__attribute__((used)) static int ds1307_add_frequency_test(struct ds1307 *ds1307)
{
	int err;

	switch (ds1307->type) {
	case m41t0:
	case m41t00:
	case m41t11:
		err = rtc_add_group(ds1307->rtc, &rtc_freq_test_attr_group);
		if (err)
			return err;
		break;
	default:
		break;
	}

	return 0;
}