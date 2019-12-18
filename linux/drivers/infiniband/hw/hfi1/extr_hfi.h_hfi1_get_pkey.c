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
typedef  scalar_t__ u16 ;
struct hfi1_pportdata {scalar_t__* pkeys; } ;
struct hfi1_ibport {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 

__attribute__((used)) static inline u16 hfi1_get_pkey(struct hfi1_ibport *ibp, unsigned index)
{
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u16 ret;

	if (index >= ARRAY_SIZE(ppd->pkeys))
		ret = 0;
	else
		ret = ppd->pkeys[index];

	return ret;
}