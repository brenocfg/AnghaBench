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
struct csi2tx_fmt {scalar_t__ mbus; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct csi2tx_fmt const*) ; 
 struct csi2tx_fmt const* csi2tx_formats ; 

__attribute__((used)) static const struct csi2tx_fmt *csi2tx_get_fmt_from_mbus(u32 mbus)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(csi2tx_formats); i++)
		if (csi2tx_formats[i].mbus == mbus)
			return &csi2tx_formats[i];

	return NULL;
}