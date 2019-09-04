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
struct wf_fcu_priv {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int wf_fcu_write_reg(struct wf_fcu_priv *pv, int reg,
			    const unsigned char *ptr, int nb)
{
	int tries, nw;
	unsigned char buf[16];

	buf[0] = reg;
	memcpy(buf+1, ptr, nb);
	++nb;
	tries = 0;
	for (;;) {
		nw = i2c_master_send(pv->i2c, buf, nb);
		if (nw > 0 || (nw < 0 && nw != -EIO) || tries >= 100)
			break;
		msleep(10);
		++tries;
	}
	if (nw < 0)
		pr_err("wf_fcu: Failure writing to FCU: %d", nw);
	return nw;
}