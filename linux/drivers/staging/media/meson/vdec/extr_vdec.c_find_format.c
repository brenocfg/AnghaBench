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
typedef  unsigned int u32 ;
struct amvdec_format {unsigned int pixfmt; } ;

/* Variables and functions */

__attribute__((used)) static const struct amvdec_format *
find_format(const struct amvdec_format *fmts, u32 size, u32 pixfmt)
{
	unsigned int i;

	for (i = 0; i < size; i++) {
		if (fmts[i].pixfmt == pixfmt)
			return &fmts[i];
	}

	return NULL;
}