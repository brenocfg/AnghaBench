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
typedef  int u8 ;
typedef  unsigned long long __u64 ;

/* Variables and functions */
 int BIT (int) ; 
 char* strchr (char const*,char const) ; 

__attribute__((used)) static u8 input_name2mask(const char *name, __u64 *mask, __u64 *value,
			  u8 *imask, u8 *omask)
{
	const char sigtab[] = "EeSsPpAaBb";
	u8 im, om;
	__u64 m, v;

	om = 0;
	im = 0;
	m = 0ULL;
	v = 0ULL;
	while (*name) {
		int in, out, bit, neg;
		const char *idx;

		idx = strchr(sigtab, *name);
		if (!idx)
			return 0;	/* input name not found */

		in = idx - sigtab;
		neg = (in & 1);	/* odd (lower) names are negated */
		in >>= 1;
		im |= BIT(in);

		name++;
		if (*name >= '0' && *name <= '7') {
			out = *name - '0';
			om |= BIT(out);
		} else if (*name == '-') {
			out = 8;
		} else {
			return 0;	/* unknown bit name */
		}

		bit = (out * 5) + in;

		m |= 1ULL << bit;
		if (!neg)
			v |= 1ULL << bit;
		name++;
	}
	*mask = m;
	*value = v;
	if (imask)
		*imask |= im;
	if (omask)
		*omask |= om;
	return 1;
}