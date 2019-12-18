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
struct csis_pix_format {scalar_t__ code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct csis_pix_format const*) ; 
 struct csis_pix_format const* mipi_csis_formats ; 

__attribute__((used)) static const struct csis_pix_format *find_csis_format(u32 code)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(mipi_csis_formats); i++)
		if (code == mipi_csis_formats[i].code)
			return &mipi_csis_formats[i];
	return NULL;
}