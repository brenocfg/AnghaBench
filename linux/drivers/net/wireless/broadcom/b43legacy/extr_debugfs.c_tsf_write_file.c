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
typedef  int /*<<< orphan*/  u64 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  b43legacy_tsf_write (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,unsigned long long*) ; 

__attribute__((used)) static int tsf_write_file(struct b43legacy_wldev *dev, const char *buf, size_t count)
{
	u64 tsf;

	if (sscanf(buf, "%llu", (unsigned long long *)(&tsf)) != 1)
		return -EINVAL;
	b43legacy_tsf_write(dev, tsf);

	return 0;
}