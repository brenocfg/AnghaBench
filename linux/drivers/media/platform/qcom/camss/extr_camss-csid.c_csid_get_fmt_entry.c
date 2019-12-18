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
struct csid_format {scalar_t__ code; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static const struct csid_format *csid_get_fmt_entry(
					const struct csid_format *formats,
					unsigned int nformat,
					u32 code)
{
	unsigned int i;

	for (i = 0; i < nformat; i++)
		if (code == formats[i].code)
			return &formats[i];

	WARN(1, "Unknown format\n");

	return &formats[0];
}