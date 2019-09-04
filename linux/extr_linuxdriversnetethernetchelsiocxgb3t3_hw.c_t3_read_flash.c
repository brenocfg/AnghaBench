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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SF_RD_DATA_FAST ; 
 unsigned int SF_SIZE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int sf1_read (struct adapter*,int,int,int /*<<< orphan*/ *) ; 
 int sf1_write (struct adapter*,int,int,unsigned int) ; 
 unsigned int swab32 (unsigned int) ; 

__attribute__((used)) static int t3_read_flash(struct adapter *adapter, unsigned int addr,
			 unsigned int nwords, u32 *data, int byte_oriented)
{
	int ret;

	if (addr + nwords * sizeof(u32) > SF_SIZE || (addr & 3))
		return -EINVAL;

	addr = swab32(addr) | SF_RD_DATA_FAST;

	if ((ret = sf1_write(adapter, 4, 1, addr)) != 0 ||
	    (ret = sf1_read(adapter, 1, 1, data)) != 0)
		return ret;

	for (; nwords; nwords--, data++) {
		ret = sf1_read(adapter, 4, nwords > 1, data);
		if (ret)
			return ret;
		if (byte_oriented)
			*data = htonl(*data);
	}
	return 0;
}