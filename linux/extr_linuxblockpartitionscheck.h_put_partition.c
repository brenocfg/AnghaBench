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
typedef  int /*<<< orphan*/  tmp ;
struct parsed_partitions {int limit; char* name; int /*<<< orphan*/  pp_buf; TYPE_1__* parts; } ;
typedef  void* sector_t ;
struct TYPE_2__ {void* size; void* from; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDEVNAME_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
put_partition(struct parsed_partitions *p, int n, sector_t from, sector_t size)
{
	if (n < p->limit) {
		char tmp[1 + BDEVNAME_SIZE + 10 + 1];

		p->parts[n].from = from;
		p->parts[n].size = size;
		snprintf(tmp, sizeof(tmp), " %s%d", p->name, n);
		strlcat(p->pp_buf, tmp, PAGE_SIZE);
	}
}