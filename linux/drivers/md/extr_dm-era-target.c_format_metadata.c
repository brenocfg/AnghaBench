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
struct era_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int create_fresh_metadata (struct era_metadata*) ; 
 int /*<<< orphan*/  dm_sm_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_destroy (int /*<<< orphan*/ ) ; 
 int write_superblock (struct era_metadata*) ; 

__attribute__((used)) static int format_metadata(struct era_metadata *md)
{
	int r;

	r = create_fresh_metadata(md);
	if (r)
		return r;

	r = write_superblock(md);
	if (r) {
		dm_sm_destroy(md->sm);
		dm_tm_destroy(md->tm);
		return r;
	}

	return 0;
}