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
struct wf_fcu_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int wf_fcu_read_reg(struct wf_fcu_priv *pv, int reg,
			   unsigned char *buf, int nb)
{
	int tries, nr, nw;

	mutex_lock(&pv->lock);

	buf[0] = reg;
	tries = 0;
	for (;;) {
		nw = i2c_master_send(pv->i2c, buf, 1);
		if (nw > 0 || (nw < 0 && nw != -EIO) || tries >= 100)
			break;
		msleep(10);
		++tries;
	}
	if (nw <= 0) {
		pr_err("Failure writing address to FCU: %d", nw);
		nr = nw;
		goto bail;
	}
	tries = 0;
	for (;;) {
		nr = i2c_master_recv(pv->i2c, buf, nb);
		if (nr > 0 || (nr < 0 && nr != -ENODEV) || tries >= 100)
			break;
		msleep(10);
		++tries;
	}
	if (nr <= 0)
		pr_err("wf_fcu: Failure reading data from FCU: %d", nw);
 bail:
	mutex_unlock(&pv->lock);
	return nr;
}