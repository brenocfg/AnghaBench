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
typedef  scalar_t__ u32 ;
struct soc_mbus_pixelfmt {int dummy; } ;
struct soc_mbus_lookup {scalar_t__ code; struct soc_mbus_pixelfmt const fmt; } ;

/* Variables and functions */

const struct soc_mbus_pixelfmt *soc_mbus_find_fmtdesc(
	u32 code,
	const struct soc_mbus_lookup *lookup,
	int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (lookup[i].code == code)
			return &lookup[i].fmt;

	return NULL;
}