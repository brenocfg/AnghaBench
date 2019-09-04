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

/* Variables and functions */
 int /*<<< orphan*/  isxdigit (char) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 char toupper (char const) ; 

__attribute__((used)) static bool matching_id(const char *idstr, const char *list_id)
{
	int i;

	if (memcmp(idstr, list_id, 3))
		return false;

	for (i = 3; i < 7; i++) {
		char c = toupper(idstr[i]);

		if (!isxdigit(c)
		    || (list_id[i] != 'X' && c != toupper(list_id[i])))
			return false;
	}
	return true;
}