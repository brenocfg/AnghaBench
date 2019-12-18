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
struct isi_format {unsigned int fourcc; } ;
struct atmel_isi {unsigned int num_user_formats; struct isi_format** user_formats; } ;

/* Variables and functions */

__attribute__((used)) static const struct isi_format *find_format_by_fourcc(struct atmel_isi *isi,
						      unsigned int fourcc)
{
	unsigned int num_formats = isi->num_user_formats;
	const struct isi_format *fmt;
	unsigned int i;

	for (i = 0; i < num_formats; i++) {
		fmt = isi->user_formats[i];
		if (fmt->fourcc == fourcc)
			return fmt;
	}

	return NULL;
}