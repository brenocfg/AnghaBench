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
struct wf_sat {int /*<<< orphan*/  last_read; int /*<<< orphan*/  cache; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static int wf_sat_read_cache(struct wf_sat *sat)
{
	int err;

	err = i2c_smbus_read_i2c_block_data(sat->i2c, 0x3f, 16, sat->cache);
	if (err < 0)
		return err;
	sat->last_read = jiffies;
#ifdef LOTSA_DEBUG
	{
		int i;
		DBG(KERN_DEBUG "wf_sat_get: data is");
		for (i = 0; i < 16; ++i)
			DBG(" %.2x", sat->cache[i]);
		DBG("\n");
	}
#endif
	return 0;
}