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
struct sf_buffer {unsigned long* sdbt; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,unsigned long*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 unsigned long* get_next_sdbt (unsigned long*) ; 
 scalar_t__ is_link_entry (unsigned long*) ; 
 int /*<<< orphan*/  memset (struct sf_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sfdbg ; 

__attribute__((used)) static void free_sampling_buffer(struct sf_buffer *sfb)
{
	unsigned long *sdbt, *curr;

	if (!sfb->sdbt)
		return;

	sdbt = sfb->sdbt;
	curr = sdbt;

	/* Free the SDBT after all SDBs are processed... */
	while (1) {
		if (!*curr || !sdbt)
			break;

		/* Process table-link entries */
		if (is_link_entry(curr)) {
			curr = get_next_sdbt(curr);
			if (sdbt)
				free_page((unsigned long) sdbt);

			/* If the origin is reached, sampling buffer is freed */
			if (curr == sfb->sdbt)
				break;
			else
				sdbt = curr;
		} else {
			/* Process SDB pointer */
			if (*curr) {
				free_page(*curr);
				curr++;
			}
		}
	}

	debug_sprintf_event(sfdbg, 5,
			    "free_sampling_buffer: freed sdbt=%p\n", sfb->sdbt);
	memset(sfb, 0, sizeof(*sfb));
}