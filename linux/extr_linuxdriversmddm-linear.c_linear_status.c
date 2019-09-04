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
struct linear_c {TYPE_1__* dev; scalar_t__ start; } ;
struct dm_target {scalar_t__ private; } ;
typedef  int status_type_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,char*,unsigned long long) ; 

__attribute__((used)) static void linear_status(struct dm_target *ti, status_type_t type,
			  unsigned status_flags, char *result, unsigned maxlen)
{
	struct linear_c *lc = (struct linear_c *) ti->private;

	switch (type) {
	case STATUSTYPE_INFO:
		result[0] = '\0';
		break;

	case STATUSTYPE_TABLE:
		snprintf(result, maxlen, "%s %llu", lc->dev->name,
				(unsigned long long)lc->start);
		break;
	}
}