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
struct i2400m {TYPE_1__* bus_bm_pokes_table; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ address; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_download_chunk (struct i2400m*,int /*<<< orphan*/ *,int,scalar_t__,int,int) ; 

__attribute__((used)) static
int i2400m_dnload_init_nonsigned(struct i2400m *i2400m)
{
	unsigned i = 0;
	int ret = 0;
	struct device *dev = i2400m_dev(i2400m);
	d_fnstart(5, dev, "(i2400m %p)\n", i2400m);
	if (i2400m->bus_bm_pokes_table) {
		while (i2400m->bus_bm_pokes_table[i].address) {
			ret = i2400m_download_chunk(
				i2400m,
				&i2400m->bus_bm_pokes_table[i].data,
				sizeof(i2400m->bus_bm_pokes_table[i].data),
				i2400m->bus_bm_pokes_table[i].address, 1, 1);
			if (ret < 0)
				break;
			i++;
		}
	}
	d_fnend(5, dev, "(i2400m %p) = %d\n", i2400m, ret);
	return ret;
}