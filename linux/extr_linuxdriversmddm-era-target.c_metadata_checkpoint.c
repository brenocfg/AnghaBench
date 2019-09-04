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
struct era_metadata {int dummy; } ;

/* Variables and functions */
 int metadata_era_rollover (struct era_metadata*) ; 

__attribute__((used)) static int metadata_checkpoint(struct era_metadata *md)
{
	/*
	 * For now we just rollover, but later I want to put a check in to
	 * avoid this if the filter is still pretty fresh.
	 */
	return metadata_era_rollover(md);
}