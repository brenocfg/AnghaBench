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
struct venus_caps {size_t num_fmts; int /*<<< orphan*/ * fmts; } ;
struct raw_formats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct raw_formats const*,unsigned int) ; 

__attribute__((used)) static void fill_raw_fmts(struct venus_caps *cap, const void *fmts,
			  unsigned int num_fmts)
{
	const struct raw_formats *formats = fmts;

	memcpy(&cap->fmts[cap->num_fmts], formats, num_fmts * sizeof(*formats));
	cap->num_fmts += num_fmts;
}