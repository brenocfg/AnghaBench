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
struct era {int /*<<< orphan*/  digest; TYPE_1__* md; } ;
struct TYPE_2__ {int archived_writesets; } ;

/* Variables and functions */
 int /*<<< orphan*/  metadata_digest_start (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kick_off_digest(struct era *era)
{
	if (era->md->archived_writesets) {
		era->md->archived_writesets = false;
		metadata_digest_start(era->md, &era->digest);
	}
}