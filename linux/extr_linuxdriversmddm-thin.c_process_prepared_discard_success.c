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
struct dm_thin_new_mapping {int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_discard_mapping (struct dm_thin_new_mapping*) ; 

__attribute__((used)) static void process_prepared_discard_success(struct dm_thin_new_mapping *m)
{
	bio_endio(m->bio);
	free_discard_mapping(m);
}