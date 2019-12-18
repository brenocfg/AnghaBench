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
struct dvb_ca_en50221 {struct cxd* data; } ;
struct cxd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_mode (struct cxd*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mode (struct cxd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_regm (struct cxd*,int,int,int) ; 

__attribute__((used)) static int slot_ts_enable(struct dvb_ca_en50221 *ca, int slot)
{
	struct cxd *ci = ca->data;

	mutex_lock(&ci->lock);
	write_regm(ci, 0x09, 0x00, 0x08);
	set_mode(ci, 0);
	cam_mode(ci, 1);
	mutex_unlock(&ci->lock);
	return 0;
}