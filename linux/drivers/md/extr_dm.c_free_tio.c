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
struct dm_target_io {int /*<<< orphan*/  clone; scalar_t__ inside_dm_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_tio(struct dm_target_io *tio)
{
	if (tio->inside_dm_io)
		return;
	bio_put(&tio->clone);
}