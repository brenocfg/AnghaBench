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
struct ib_user_mad_hdr {scalar_t__ lid; int /*<<< orphan*/  gid; scalar_t__ grh_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int same_destination(struct ib_user_mad_hdr *hdr1,
			    struct ib_user_mad_hdr *hdr2)
{
	if (!hdr1->grh_present && !hdr2->grh_present)
	   return (hdr1->lid == hdr2->lid);

	if (hdr1->grh_present && hdr2->grh_present)
	   return !memcmp(hdr1->gid, hdr2->gid, 16);

	return 0;
}