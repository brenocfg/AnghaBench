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
struct std_name {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct std_name *find_std_name(const struct std_name *arrPtr,
					    unsigned int arrSize,
					    const char *bufPtr,
					    unsigned int bufSize)
{
	unsigned int idx;
	const struct std_name *p;
	for (idx = 0; idx < arrSize; idx++) {
		p = arrPtr + idx;
		if (strlen(p->name) != bufSize) continue;
		if (!memcmp(bufPtr,p->name,bufSize)) return p;
	}
	return NULL;
}