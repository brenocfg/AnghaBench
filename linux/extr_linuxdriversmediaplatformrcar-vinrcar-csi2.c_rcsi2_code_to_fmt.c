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
struct rcar_csi2_format {unsigned int code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct rcar_csi2_format const*) ; 
 struct rcar_csi2_format const* rcar_csi2_formats ; 

__attribute__((used)) static const struct rcar_csi2_format *rcsi2_code_to_fmt(unsigned int code)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(rcar_csi2_formats); i++)
		if (rcar_csi2_formats[i].code == code)
			return &rcar_csi2_formats[i];

	return NULL;
}