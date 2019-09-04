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
struct era_metadata {int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int EPERM ; 
 int format_metadata (struct era_metadata*) ; 
 int open_metadata (struct era_metadata*) ; 
 int superblock_all_zeroes (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int open_or_format_metadata(struct era_metadata *md,
				   bool may_format)
{
	int r;
	bool unformatted = false;

	r = superblock_all_zeroes(md->bm, &unformatted);
	if (r)
		return r;

	if (unformatted)
		return may_format ? format_metadata(md) : -EPERM;

	return open_metadata(md);
}