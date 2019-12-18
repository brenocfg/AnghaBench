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
struct message_header {int present; } ;

/* Variables and functions */
 int GRU_CACHE_LINE_BYTES ; 

__attribute__((used)) static inline int get_present2(void *p)
{
	struct message_header *mhdr = p + GRU_CACHE_LINE_BYTES;
	return mhdr->present;
}