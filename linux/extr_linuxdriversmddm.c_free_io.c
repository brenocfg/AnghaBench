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
struct mapped_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clone; } ;
struct dm_io {TYPE_1__ tio; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_io(struct mapped_device *md, struct dm_io *io)
{
	bio_put(&io->tio.clone);
}