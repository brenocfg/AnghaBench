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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,char const) ; 

ssize_t bch_hprint(char *buf, int64_t v)
{
	static const char units[] = "?kMGTPEZY";
	int u = 0, t;

	uint64_t q;

	if (v < 0)
		q = -v;
	else
		q = v;

	/* For as long as the number is more than 3 digits, but at least
	 * once, shift right / divide by 1024.  Keep the remainder for
	 * a digit after the decimal point.
	 */
	do {
		u++;

		t = q & ~(~0 << 10);
		q >>= 10;
	} while (q >= 1000);

	if (v < 0)
		/* '-', up to 3 digits, '.', 1 digit, 1 character, null;
		 * yields 8 bytes.
		 */
		return sprintf(buf, "-%llu.%i%c", q, t * 10 / 1024, units[u]);
	else
		return sprintf(buf, "%llu.%i%c", q, t * 10 / 1024, units[u]);
}