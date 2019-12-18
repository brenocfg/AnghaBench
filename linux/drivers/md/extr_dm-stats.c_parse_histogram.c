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
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long long* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,unsigned long long*,char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int parse_histogram(const char *h, unsigned *n_histogram_entries,
			   unsigned long long **histogram_boundaries)
{
	const char *q;
	unsigned n;
	unsigned long long last;

	*n_histogram_entries = 1;
	for (q = h; *q; q++)
		if (*q == ',')
			(*n_histogram_entries)++;

	*histogram_boundaries = kmalloc_array(*n_histogram_entries,
					      sizeof(unsigned long long),
					      GFP_KERNEL);
	if (!*histogram_boundaries)
		return -ENOMEM;

	n = 0;
	last = 0;
	while (1) {
		unsigned long long hi;
		int s;
		char ch;
		s = sscanf(h, "%llu%c", &hi, &ch);
		if (!s || (s == 2 && ch != ','))
			return -EINVAL;
		if (hi <= last)
			return -EINVAL;
		last = hi;
		(*histogram_boundaries)[n] = hi;
		if (s == 1)
			return 0;
		h = strchr(h, ',') + 1;
		n++;
	}
}