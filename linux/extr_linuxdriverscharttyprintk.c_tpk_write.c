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
struct ttyprintk_port {int /*<<< orphan*/  port_write_mutex; } ;
struct tty_struct {struct ttyprintk_port* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tpk_printk (unsigned char const*,int) ; 

__attribute__((used)) static int tpk_write(struct tty_struct *tty,
		const unsigned char *buf, int count)
{
	struct ttyprintk_port *tpkp = tty->driver_data;
	int ret;


	/* exclusive use of tpk_printk within this tty */
	mutex_lock(&tpkp->port_write_mutex);
	ret = tpk_printk(buf, count);
	mutex_unlock(&tpkp->port_write_mutex);

	return ret;
}