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
typedef  int v4l2_std_id ;
struct std_name {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct std_name* find_std_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  std_groups ; 
 int /*<<< orphan*/  std_items ; 

int pvr2_std_str_to_id(v4l2_std_id *idPtr,const char *bufPtr,
		       unsigned int bufSize)
{
	v4l2_std_id id = 0;
	v4l2_std_id cmsk = 0;
	v4l2_std_id t;
	int mMode = 0;
	unsigned int cnt;
	char ch;
	const struct std_name *sp;

	while (bufSize) {
		if (!mMode) {
			cnt = 0;
			while ((cnt < bufSize) && (bufPtr[cnt] != '-')) cnt++;
			if (cnt >= bufSize) return 0; // No more characters
			sp = find_std_name(std_groups, ARRAY_SIZE(std_groups),
					   bufPtr,cnt);
			if (!sp) return 0; // Illegal color system name
			cnt++;
			bufPtr += cnt;
			bufSize -= cnt;
			mMode = !0;
			cmsk = sp->id;
			continue;
		}
		cnt = 0;
		while (cnt < bufSize) {
			ch = bufPtr[cnt];
			if (ch == ';') {
				mMode = 0;
				break;
			}
			if (ch == '/') break;
			cnt++;
		}
		sp = find_std_name(std_items, ARRAY_SIZE(std_items),
				   bufPtr,cnt);
		if (!sp) return 0; // Illegal modulation system ID
		t = sp->id & cmsk;
		if (!t) return 0; // Specific color + modulation system illegal
		id |= t;
		if (cnt < bufSize) cnt++;
		bufPtr += cnt;
		bufSize -= cnt;
	}

	if (idPtr) *idPtr = id;
	return !0;
}