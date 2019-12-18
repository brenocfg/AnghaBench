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
struct cxgbi_ppod_data {unsigned long caller_data; int npods; int color; } ;
struct cxgbi_ppm {struct cxgbi_ppod_data* ppod_data; } ;

/* Variables and functions */
 int PPOD_IDX_SHIFT ; 

__attribute__((used)) static void ppm_mark_entries(struct cxgbi_ppm *ppm, int i, int count,
			     unsigned long caller_data)
{
	struct cxgbi_ppod_data *pdata = ppm->ppod_data + i;

	pdata->caller_data = caller_data;
	pdata->npods = count;

	if (pdata->color == ((1 << PPOD_IDX_SHIFT) - 1))
		pdata->color = 0;
	else
		pdata->color++;
}