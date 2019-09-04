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
struct dvb_ca_en50221 {struct cxd* data; } ;
struct cxd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_pccard (struct cxd*,int,int*,int) ; 
 int /*<<< orphan*/  set_mode (struct cxd*,int) ; 

__attribute__((used)) static int read_attribute_mem(struct dvb_ca_en50221 *ca,
			      int slot, int address)
{
	struct cxd *ci = ca->data;
	u8 val;

	mutex_lock(&ci->lock);
	set_mode(ci, 1);
	read_pccard(ci, address, &val, 1);
	mutex_unlock(&ci->lock);
	return val;
}