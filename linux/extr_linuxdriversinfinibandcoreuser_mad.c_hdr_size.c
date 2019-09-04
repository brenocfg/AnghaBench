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
struct ib_user_mad_hdr_old {int dummy; } ;
struct ib_user_mad_hdr {int dummy; } ;
struct ib_umad_file {scalar_t__ use_pkey_index; } ;

/* Variables and functions */

__attribute__((used)) static int hdr_size(struct ib_umad_file *file)
{
	return file->use_pkey_index ? sizeof (struct ib_user_mad_hdr) :
		sizeof (struct ib_user_mad_hdr_old);
}