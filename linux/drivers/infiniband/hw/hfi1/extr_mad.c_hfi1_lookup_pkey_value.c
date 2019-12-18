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
struct hfi1_ibport {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 

__attribute__((used)) static u16 hfi1_lookup_pkey_value(struct hfi1_ibport *ibp, int pkey_idx)
{
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	if (pkey_idx < ARRAY_SIZE(ppd->pkeys))
		return ppd->pkeys[pkey_idx];

	return 0;
}