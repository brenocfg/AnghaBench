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
struct imgchunk {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct imgchunk*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_chunks(struct imgchunk *fchunk, unsigned int *nfchunks)
{
	int i;

	for (i = 0; i < *nfchunks; i++)
		kfree(fchunk[i].data);

	*nfchunks = 0;
	memset(fchunk, 0, sizeof(*fchunk));
}