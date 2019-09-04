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
typedef  int u8 ;

/* Variables and functions */
 int kvm_s390_query_ap_config (int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ test_facility (int) ; 

__attribute__((used)) static int kvm_s390_apxa_installed(void)
{
	u8 config[128];
	int cc;

	if (test_facility(12)) {
		cc = kvm_s390_query_ap_config(config);

		if (cc)
			pr_err("PQAP(QCI) failed with cc=%d", cc);
		else
			return config[0] & 0x40;
	}

	return 0;
}