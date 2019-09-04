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
struct device {int dummy; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH_KEYSC_MAXKEYS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*,int,unsigned long) ; 

__attribute__((used)) static void sh_keysc_map_dbg(struct device *dev, unsigned long *map,
			     const char *str)
{
	int k;

	for (k = 0; k < BITS_TO_LONGS(SH_KEYSC_MAXKEYS); k++)
		dev_dbg(dev, "%s[%d] 0x%lx\n", str, k, map[k]);
}