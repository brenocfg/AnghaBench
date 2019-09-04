#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * plane; int /*<<< orphan*/ * uv_plane; } ;
struct skl_ddb_values {TYPE_1__ ddb; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
skl_copy_ddb_for_pipe(struct skl_ddb_values *dst,
		      struct skl_ddb_values *src,
		      enum pipe pipe)
{
	memcpy(dst->ddb.uv_plane[pipe], src->ddb.uv_plane[pipe],
	       sizeof(dst->ddb.uv_plane[pipe]));
	memcpy(dst->ddb.plane[pipe], src->ddb.plane[pipe],
	       sizeof(dst->ddb.plane[pipe]));
}