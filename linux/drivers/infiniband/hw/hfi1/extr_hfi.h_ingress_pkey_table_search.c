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
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_pportdata {int /*<<< orphan*/ * pkeys; } ;

/* Variables and functions */
 int MAX_PKEY_VALUES ; 
 scalar_t__ ingress_pkey_matches_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ingress_pkey_table_search(struct hfi1_pportdata *ppd, u16 pkey)
{
	int i;

	for (i = 0; i < MAX_PKEY_VALUES; i++) {
		if (ingress_pkey_matches_entry(pkey, ppd->pkeys[i]))
			return 0;
	}
	return 1;
}